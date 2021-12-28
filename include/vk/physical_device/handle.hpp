#pragma once

#include <core/elements/of_type.hpp>
#include <core/elements/one_of.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/forward.hpp>
#include <core/range/of_value_type.hpp>
#include <core/span.hpp>

#include "properties.hpp"
#include "memory_properties.hpp"
#include "queue_family_properties.hpp"
#include "../surface/capabilities.hpp"
#include "../surface/present_mode.hpp"
#include "../surface/format.hpp"
#include "../surface/handle.hpp"
#include "../shared/result.hpp"
#include "../shared/queue_family_index.hpp"
#include "../shared/count.hpp"
#include "../shared/extension_name.hpp"
#include "../shared/extension_properties.hpp"
#include "../shared/guarded_handle.hpp"
#include "../shared/handle.hpp"

namespace vk {

	struct device;
	struct surface;
	struct physical_device;

	template<>
	struct vk::handle<vk::physical_device> : vk::handle_base<vk::dispatchable> {

		template<typename... Args>
		vk::handle<vk::device> create_device(Args&&... args) const;

		template<typename... Args>
		vk::guarded_handle<vk::device> create_guarded_device(Args&&... args) const;

		vk::physical_device_properties get_properties() const {
			vk::physical_device_properties props;
			vkGetPhysicalDeviceProperties(
				(VkPhysicalDevice) vk::get_handle_value(*this),
				(VkPhysicalDeviceProperties*) &props
			);
			return props;
		}

		vk::physical_device_memory_properties get_memory_properties() const {
			vk::physical_device_memory_properties props;
			vkGetPhysicalDeviceMemoryProperties(
				(VkPhysicalDevice) vk::get_handle_value(*this),
				(VkPhysicalDeviceMemoryProperties*) &props
			);
			return props;
		}

		vk::count get_queue_family_properties(range::of_value_type<vk::queue_family_properties> auto&& range) const {
			uint32 count = (uint32) range.size();

			vkGetPhysicalDeviceQueueFamilyProperties(
				(VkPhysicalDevice) vk::get_handle_value(*this),
				&count,
				(VkQueueFamilyProperties*) range.data()
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
		requires(types::are_same::for_types_of<Args..., vk::queue_flag>)
		vk::queue_family_index get_first_queue_family_index_with_capabilities(Args... args) const {
			uint32 count = (uint32)queue_family_properties_count();
			vk::queue_family_properties props[count];
			get_queue_family_properties(span{ props, count });

			uint32 index = 0;
			for(vk::queue_family_properties p : span{ props, count }) {
				if((p.flags.get(args) && ...)) return { index };
				++index;
			}

			return { VK_QUEUE_FAMILY_IGNORED };
		}

		vk::count for_each_queue_family_properties(auto&& f) const {
			return view_queue_family_properties(
				[&](auto view) {
					for(auto props : view) f(props);
				}
			);
		}

		elements::one_of<vk::result, vk::count>
		try_enumerate_extension_properties(range::of_value_type<vk::extension_properties> auto&& props, vk::extension_name extension_name) const {
			uint32 count = (uint32) props.size();
			const char* name = extension_name.begin();

			vk::result result {
				(int32) vkEnumerateDeviceExtensionProperties(
					(VkPhysicalDevice) vk::get_handle_value(*this),
					name,
					&count,
					(VkExtensionProperties*) props.data()
				)
			};

			if(result.success()) return vk::count{ count };
			return result;
		}

		elements::one_of<vk::result, vk::count>
		try_get_extension_properties_count(vk::extension_name name = {}) const {
			return try_enumerate_extension_properties(span<vk::extension_properties>{ nullptr, 0 }, name);
		}

		vk::count get_extension_properties_count(vk::extension_name name = {}) const {
			auto result = try_get_extension_properties_count(name);
			if(result.is_current<vk::result>()) throw result.get<vk::result>();
			return result.get<vk::count>();
		}

		elements::one_of<vk::result, vk::count>
		try_view_extension_properties(vk::count count, auto&& f, vk::extension_name name = {}) const {
			vk::extension_properties props[(uint32) count];
			auto result = try_enumerate_extension_properties(span{ props, (uint32) count }, name);
			if(result.is_current<vk::result>()) return result;

			count = result.get<vk::count>();
			f(span{ props, (uint32) count });
			return count;
		}

		template<typename F>
		vk::count view_extension_properties(vk::count count, F&& f, vk::extension_name name = {}) const {
			auto result = try_view_extension_properties(count, forward<F>(f), name);
			if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
			return result.template get<vk::count>();
		}

		template<typename F>
		elements::one_of<vk::result, vk::count>
		try_view_extension_properties(F&& f, vk::extension_name name = {}) const {
			auto result = try_get_extension_properties_count(name);
			if(result.is_current<vk::result>()) return result.get<vk::result>();
			vk::count count = result.get<vk::count>();
			return try_view_extension_properties(
				count,
				forward<F>(f),
				name
			);
		}

		template<typename F>
		vk::count view_extension_properties(F&& f, vk::extension_name name = {}) const {
			auto result = try_view_extension_properties(forward<F>(f), name);
			if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
			return result.template get<vk::count>();
		}

		elements::one_of<vk::result, vk::count>
		try_for_each_extension_properties(auto&& f) {
			return try_view_extension_properties([&](auto view) {
				for(auto props : view) f(props);
			});
		}

		template<typename F>
		vk::count for_each_extension_properties(F&& f) {
			auto result = try_for_each_extension_properties(forward<F>(f));
			if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
			return result.template get<vk::count>();
		}

		elements::one_of<vk::result, vk::surface_capabilities>
		try_get_surface_capabilities(vk::ordinary_or_guarded_handle<vk::surface> auto& surface) const {
			vk::surface_capabilities caps;
 
			vk::result result {
				(int32) vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
					(VkPhysicalDevice) vk::get_handle_value(*this),
					(VkSurfaceKHR) vk::get_handle_value(surface),
					(VkSurfaceCapabilitiesKHR*) &caps
				)
			};
			if(result.success()) return caps;
			return result;
		}

		vk::surface_capabilities get_surface_capabilities(vk::ordinary_or_guarded_handle<vk::surface> auto& surface) const {
			auto result = try_get_surface_capabilities(surface);
			if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
			return result.template get<vk::surface_capabilities>();
		}

		elements::one_of<vk::result, vk::count>
		try_get_surface_formats(vk::ordinary_or_guarded_handle<vk::surface> auto& surface, range::of_value_type<vk::surface_format> auto&& formats) const {
			uint32 count = (uint32) formats.size();
 
			vk::result result {
				(int32) vkGetPhysicalDeviceSurfaceFormatsKHR(
					(VkPhysicalDevice) vk::get_handle_value(*this),
					(VkSurfaceKHR) vk::get_handle_value(surface),
					&count,
					(VkSurfaceFormatKHR*) formats.data()
				)
			};

			if(result.success() || result.incomplete()) return vk::count{ count };

			return result;
		}

		template<range::of_value_type<vk::surface_format> FormatsRange>
		vk::count get_surface_formats(vk::ordinary_or_guarded_handle<vk::surface> auto& surface, FormatsRange&& formats) const {
			auto result = try_get_surface_formats(surface, forward<FormatsRange>(formats));
			if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
			return result.template get<vk::count>();
		}

		elements::one_of<vk::result, vk::count>
		try_get_surface_formats_count(vk::ordinary_or_guarded_handle<vk::surface> auto& surface) const {
			return try_get_surface_formats(surface, span<vk::surface_format>{ nullptr, 0 });
		}

		vk::count get_surface_formats_count(vk::ordinary_or_guarded_handle<vk::surface> auto& surface) const {
			auto result = try_get_surface_formats_count(surface);
			if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
			return result.template get<vk::count>();
		}

		elements::one_of<vk::result, vk::count>
		try_view_surface_formats(vk::ordinary_or_guarded_handle<vk::surface> auto& surface, vk::count count, auto&& f) const {
			vk::surface_format formats[(uint32) count];
			auto result = try_get_surface_formats(surface, span{ formats, (uint32) count });
			if(result.template is_current<vk::result>()) return result;
			count = result.template get<vk::count>();
			f(span{ formats, (uint32) count });
			return count;
		}

		template<typename F>
		elements::one_of<vk::result, vk::count>
		try_view_surface_formats(vk::ordinary_or_guarded_handle<vk::surface> auto& surface, F&& f) const {
			auto result = try_get_surface_formats_count(surface);
			if(result.template is_current<vk::result>()) return result;

			return try_view_surface_formats(
				surface,
				result.template get<vk::count>(),
				forward<F>(f)
			);
		}

		template<typename F>
		vk::count view_surface_formats(vk::ordinary_or_guarded_handle<vk::surface> auto& surface, F&& f) const {
			auto result = try_view_surface_formats(surface, forward<F>(f));
			if(result.template get<vk::result>()) throw result.template get<vk::result>();
			return result.template get<vk::count>();
		}

		vk::surface_format get_first_surface_format(vk::ordinary_or_guarded_handle<vk::surface> auto& surface) const {
			vk::surface_format surface_format;
			get_surface_formats(surface, span{ &surface_format, 1 });
			return surface_format;
		}

		elements::one_of<vk::result, vk::count>
		try_get_surface_present_modes(vk::handle<vk::surface> surface, range::of_value_type<vk::present_mode> auto&& present_modes) const {
			uint32 count = (uint32) present_modes.size();

			vk::result result {
				(int32) vkGetPhysicalDeviceSurfacePresentModesKHR(
					(VkPhysicalDevice) vk::get_handle_value(*this),
					(VkSurfaceKHR) surface.value,
					&count,
					(VkPresentModeKHR*) present_modes.data()
				)
			};

			if(result.success()) return vk::count{ count };
			return result;
		}

		elements::one_of<vk::result, vk::count>
		try_get_surface_present_mode_count(vk::handle<vk::surface> surface) const {
			return try_get_surface_present_modes(surface, span<vk::present_mode>{ nullptr, 0 });
		}

		elements::one_of<vk::result, vk::count>
		try_view_surface_present_modes(vk::handle<vk::surface> surface, vk::count count, auto&& f) const {
			vk::present_mode present_modes[(uint32) count];
			auto result = try_get_surface_present_modes(surface, span{ present_modes, (uint32) count });
			if(result.is_current<vk::result>()) return result;

			count = result.get<vk::count>();
			f(span{ present_modes, (uint32) count});
			return count;
		}

		template<typename F>
		elements::one_of<vk::result, vk::count>
		try_view_surface_present_modes(vk::handle<vk::surface> surface, F&& f) const {
			auto result = try_get_surface_present_mode_count(surface);
			if(result.is_current<vk::result>()) return result;
			return try_view_surface_present_modes(
				surface,
				result.get<vk::count>(),
				forward<F>(f)
			);
		}

		elements::one_of<vk::result, vk::count>
		try_for_each_surface_presesnt_mode(vk::handle<vk::surface> surface, auto&& f) const {
			return try_view_surface_present_modes(surface, [&](auto view) {
				for(auto present_mode : view) {
					f(present_mode);
				}
			});
		}

		template<typename F>
		vk::count for_each_surface_present_mode(vk::handle<vk::surface> surface, F&& f) const {
			auto result = try_for_each_surface_presesnt_mode(surface, forward<F>(f));
			if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
			return result.template get<vk::count>();
		}
		
		template<vk::ordinary_or_guarded_handle<vk::surface> Surface>
		elements::one_of<vk::result, bool>
		try_get_surface_support(Surface&& surface, vk::queue_family_index queue_family_index) const {
			uint32 supports;

			vk::result result {
				(int32) vkGetPhysicalDeviceSurfaceSupportKHR(
					(VkPhysicalDevice) value,
					(uint32) queue_family_index,
					(VkSurfaceKHR) vk::get_handle_value(surface),
					&supports
				)
			};

			if(result.success()) return { (bool)supports };

			return result;
		}

		template<vk::ordinary_or_guarded_handle<vk::surface> Surface>
		bool get_surface_support(Surface&& surface, vk::queue_family_index queue_family_index) const {
			auto result = try_get_surface_support(forward<Surface>(surface), queue_family_index);
			if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
			return result.template get<bool>();
		}
	};

}

#include "../device/create.hpp"

template<typename... Args>
vk::handle<vk::device> vk::handle<vk::physical_device>::create_device(Args&&... args) const {
	return vk::create_device(*this, forward<Args>(args)...);
}

#include "../device/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::device> vk::handle<vk::physical_device>::create_guarded_device(Args&&... args) const {
	return { vk::create_device(*this, forward<Args>(args)...) };
}