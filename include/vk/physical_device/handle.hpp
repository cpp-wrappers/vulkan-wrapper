#pragma once

#include "properties.hpp"
#include "memory_properties.hpp"
#include "queue_family_properties.hpp"

#include "../function.hpp"
#include "../surface/capabilities.hpp"
#include "../surface/present_mode.hpp"
#include "../surface/format.hpp"
#include "../surface/handle.hpp"
#include "../handle/base.hpp"
#include "../handle/get_value.hpp"
#include "../result.hpp"
#include "../queue_family_index.hpp"
#include "../count.hpp"
#include "../extension_name.hpp"
#include "../extension_properties.hpp"
#include "../memory_type_index.hpp"
#include "../unexpected_handler.hpp"

#include <core/handle/possibly_guarded_of.hpp>
#include <core/forward.hpp>
#include <core/span.hpp>
#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/elements/one_of.hpp>

namespace vk {

	struct device;
	struct surface;
	struct physical_device;

} // vk

extern "C" VK_ATTR void VK_CALL vkGetPhysicalDeviceMemoryProperties(
	handle<vk::physical_device> physical_device,
	vk::physical_device_memory_properties* memory_properties
);

extern "C" VK_ATTR void VK_CALL vkGetPhysicalDeviceQueueFamilyProperties(
	handle<vk::physical_device> physical_device,
	uint32* queue_family_property_count,
	vk::queue_family_properties* queue_family_properties
);

extern "C" VK_ATTR int32 VK_CALL vkEnumerateDeviceExtensionProperties(
	handle<vk::physical_device> physical_device,
	const char* layer_name,
	uint32* property_count,
	vk::extension_properties* properties
);

extern "C" VK_ATTR int32 VK_CALL vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
	handle<vk::physical_device> physical_device,
	handle<vk::surface> surface,
	vk::surface_capabilities* surface_capabilities
);

extern "C" VK_ATTR int32 VK_CALL vkGetPhysicalDeviceSurfaceSupportKHR(
	handle<vk::physical_device> physical_device,
	uint32 queue_family_index,
	handle<vk::surface> surface,
	uint32* supported
);

extern "C" VK_ATTR int32 VK_CALL vkGetPhysicalDeviceSurfaceFormatsKHR(
	handle<vk::physical_device> physical_device,
	handle<vk::surface> surface,
	uint32* surface_format_count,
	vk::surface_format* surface_formats
);

extern "C" VK_ATTR int32 VK_CALL vkGetPhysicalDeviceSurfacePresentModesKHR(
	handle<vk::physical_device> physical_device,
	handle<vk::surface> surface,
	uint32* present_mode_count,
	vk::present_mode* present_modes
);

template<>
struct handle<vk::physical_device> : vk::handle_base<vk::dispatchable> {

	template<typename... Args>
	handle<vk::device> create_device(Args&&... args) const;

	template<typename... Args>
	guarded_handle<vk::device> create_guarded_device(Args&&... args) const;

	template<typename... Args>
	vk::physical_device_properties get_properties(Args&&... args) const;

	vk::physical_device_memory_properties get_memory_properties() const {
		vk::physical_device_memory_properties props;
		vkGetPhysicalDeviceMemoryProperties(
			vk::get_handle(*this),
			&props
		);
		return props;
	}

	vk::memory_type_index find_first_memory_type_index(
		vk::memory_properties required_properties,
		vk::memory_type_indices required_indices
	) const {
		auto physical_device_memory_properties = get_memory_properties();

		for(uint32 i = 0; i < physical_device_memory_properties.memory_type_count; ++i) {
			bool required_type = required_indices.at(i);
			auto memory_type = physical_device_memory_properties.memory_types[i];
			bool meets_required_properties = (memory_type.properties.value & required_properties.value) == required_properties.value;

			if(required_type && meets_required_properties) {
				return (vk::memory_type_index) i;
			}
		}

		vk::unexpected_handler();
	}

	vk::count get_queue_family_properties(range::of<vk::queue_family_properties> auto&& range) const {
		uint32 count = (uint32) range.size();

		vkGetPhysicalDeviceQueueFamilyProperties(
			vk::get_handle(*this),
			&count,
			range.data()
		);

		return { count };
	}

	vk::count queue_family_properties_count() const {
		return get_queue_family_properties(span<vk::queue_family_properties>{ nullptr, 0 });
	}

	vk::count view_queue_family_properties(vk::count count, auto&& f) const {
		vk::queue_family_properties props[(uint32) count];
		count = get_queue_family_properties(span{ props, (uint32) count });
		f(span{ props, (uint32) count });
		return count;
	}

	template<typename F>
	vk::count view_queue_family_properties(F&& f) const {
		return view_queue_family_properties(
			queue_family_properties_count(),
			forward<F>(f)
		);
	}

	template<typename... Args>
	requires(types::are_same::for_types<Args..., vk::queue_flag>)
	vk::queue_family_index find_first_queue_family_index_with_capabilities(Args... args) const {
		uint32 count = (uint32)queue_family_properties_count();
		vk::queue_family_properties props[count];
		get_queue_family_properties(span{ props, count });
		uint32 index = 0;
		for(vk::queue_family_properties p : span{ props, count }) {
			if((p.flags.get(args) && ...)) return { index };
			++index;
		}
		return { vk::queue_family_ignored };
	}

	vk::count for_each_queue_family_properties(auto&& f) const {
		return view_queue_family_properties(
			[&](auto view) {
				for(auto props : view) f(props);
			}
		);
	}

	vk::expected<vk::count>
	enumerate_extension_properties(range::of<vk::extension_properties> auto&& props, vk::extension_name extension_name) const {
		uint32 count = (uint32) props.size();
		const char* name = extension_name.begin();

		vk::result result {
			vkEnumerateDeviceExtensionProperties(
				vk::get_handle(*this),
				name,
				&count,
				props.data()
			)
		};

		if(result.error()) return result;

		return vk::count{ count };
	}

	vk::expected<vk::count>
	get_extension_properties_count(vk::extension_name name = {}) const {
		return enumerate_extension_properties(span<vk::extension_properties>{ nullptr, 0 }, name);
	}

	vk::expected<vk::count>
	view_extension_properties(vk::count count, auto&& f, vk::extension_name name = {}) const {
		vk::extension_properties props[(uint32) count];
		auto result = enumerate_extension_properties(span{ props, (uint32) count }, name);
		if(result.is_unexpected()) return result;

		count = result.get_expected();
		f(span{ props, (uint32) count });
		return count;
	}

	template<typename F>
	vk::expected<vk::count>
	view_extension_properties(F&& f, vk::extension_name name = {}) const {
		auto result = get_extension_properties_count(name);
		if(result.is_unexpected()) return result;
		vk::count count = result.get_expected();
		return view_extension_properties(
			count,
			forward<F>(f),
			name
		);
	}

	vk::expected<vk::count>
	for_each_extension_properties(auto&& f) {
		return view_extension_properties([&](auto view) {
			for(auto props : view) f(props);
		});
	}

	template<possibly_guarded_handle_of<vk::surface> Surface>
	vk::expected<vk::surface_capabilities>
	get_surface_capabilities(Surface&& surface) const {
		vk::surface_capabilities caps;

		vk::result result {
			vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
				vk::get_handle(*this),
				vk::get_handle(surface),
				&caps
			)
		};

		if(result.error()) return result;

		return caps;
	}

	vk::expected<vk::count>
	get_surface_formats(
		possibly_guarded_handle_of<vk::surface> auto& surface,
		range::of<vk::surface_format> auto&& formats
	) const {
		uint32 count = (uint32) formats.size();

		vk::result result {
			vkGetPhysicalDeviceSurfaceFormatsKHR(
				vk::get_handle(*this),
				vk::get_handle(surface),
				&count,
				formats.data()
			)
		};

		if(result.error()) return result;

		return vk::count{ count };
	}

	vk::expected<vk::surface_format>
	try_get_first_surface_format(possibly_guarded_handle_of<vk::surface> auto& surface) const {
		vk::surface_format surface_format;
		vk::expected<vk::count> result = get_surface_formats(surface, span{ &surface_format, 1 });
		if(result.is_unexpected()) return result.get_unexpected();
		return surface_format;
	}

	vk::surface_format
	get_first_surface_format(possibly_guarded_handle_of<vk::surface> auto& surface) const {
		auto result = try_get_first_surface_format(surface);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

	vk::expected<vk::count>
	get_surface_formats_count(possibly_guarded_handle_of<vk::surface> auto& surface) const {
		return get_surface_formats(surface, span<vk::surface_format>{ nullptr, 0 });
	}

	vk::expected<vk::count>
	view_surface_formats(possibly_guarded_handle_of<vk::surface> auto& surface, vk::count count, auto&& f) const {
		vk::surface_format formats[(uint32) count];
		vk::expected<vk::count> result = get_surface_formats(surface, span{ formats, (uint32) count });
		if(result.is_unexpected()) return result;
		count = result.get_expected();
		f(span{ formats, (uint32) count });
		return count;
	}

	template<typename F>
	vk::expected<vk::count>
	view_surface_formats(possibly_guarded_handle_of<vk::surface> auto& surface, F&& f) const {
		vk::expected<vk::count> result = get_surface_formats_count(surface);
		if(result.is_unexpected()) return result;

		return view_surface_formats(
			surface,
			result.get_expected(),
			forward<F>(f)
		);
	}

	vk::expected<vk::count>
	get_surface_present_modes(
		handle<vk::surface> surface,
		range::of<vk::present_mode> auto&& present_modes
	) const {
		uint32 count = (uint32) present_modes.size();

		vk::result result {
			vkGetPhysicalDeviceSurfacePresentModesKHR(
				vk::get_handle(*this),
				vk::get_handle(surface),
				&count,
				present_modes.data()
			)
		};

		if(result.error()) return result;

		return vk::count{ count };
	}

	vk::expected<vk::count>
	get_surface_present_mode_count(handle<vk::surface> surface) const {
		return get_surface_present_modes(surface, span<vk::present_mode>{ nullptr, 0 });
	}

	vk::expected<vk::count>
	view_surface_present_modes(handle<vk::surface> surface, vk::count count, auto&& f) const {
		vk::present_mode present_modes[(uint32) count];
		auto result = get_surface_present_modes(surface, span{ present_modes, (uint32) count });
		if(result.is_unexpected()) return result;
		count = result.get_expected();
		f(span{ present_modes, (uint32) count});
		return count;
	}

	template<typename F>
	vk::expected<vk::count>
	view_surface_present_modes(handle<vk::surface> surface, F&& f) const {
		auto result = get_surface_present_mode_count(surface);
		if(result.is_unexpected()) return result;
		return view_surface_present_modes(
			surface,
			result.get_expected(),
			forward<F>(f)
		);
	}

	vk::expected<vk::count>
	for_each_surface_presesnt_mode(handle<vk::surface> surface, auto&& f) const {
		return view_surface_present_modes(surface, [&](auto view) {
			for(auto present_mode : view) {
				f(present_mode);
			}
		});
	}

	template<possibly_guarded_handle_of<vk::surface> Surface>
	vk::expected<bool>
	get_surface_support(Surface&& surface, vk::queue_family_index queue_family_index) const {
		uint32 supports;

		vk::result result {
			(int32) vkGetPhysicalDeviceSurfaceSupportKHR(
				*this,
				(uint32) queue_family_index,
				vk::get_handle(surface),
				&supports
			)
		};

		if(result.error()) return result;

		return { (bool)supports };
	}

	template<typename... Args>
	void get_features(Args&&... args) const;

};

#include "get_properties.hpp"
#include "get_features.hpp"

#include "../device/create.hpp"

template<typename... Args>
handle<vk::device>
handle<vk::physical_device>::create_device(Args&&... args) const {
	return vk::create<vk::device>(*this, forward<Args>(args)...);
}

#include "../device/guarded_handle.hpp"

template<typename... Args>
guarded_handle<vk::device>
handle<vk::physical_device>::create_guarded_device(Args&&... args) const {
	auto result = vk::create<vk::device>(*this, forward<Args>(args)...);
	if(result.is_unexpected()) {
		vk::unexpected_handler(result.get_unexpected());
	}
	return { result.get_expected() };
}