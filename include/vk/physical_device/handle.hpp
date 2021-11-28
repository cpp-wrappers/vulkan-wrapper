#pragma once

#include <core/elements/of_type.hpp>
#include <core/elements/one_of.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/forward.hpp>
#include <core/type/range.hpp>
#include <core/span.hpp>

#include "properties.hpp"
#include "../shared/result.hpp"
#include "../surface/capabilities.hpp"
#include "../surface/present_mode.hpp"
#include "../shared/queue_family_index.hpp"
#include "../shared/count.hpp"
#include "queue_family_properties.hpp"
#include "../shared/extension_name.hpp"
#include "../shared/extension_properties.hpp"
#include "../surface/format.hpp"

#include "../surface/handle.hpp"

namespace vk {

	struct device;
	struct surface;

	struct physical_device {
		void* handle;

		template<typename... Args>
		vk::device create_device(Args&&... args) const;

		vk::physical_device_properties get_properties() const {
			vk::physical_device_properties props;
			vkGetPhysicalDeviceProperties(
				(VkPhysicalDevice) handle,
				(VkPhysicalDeviceProperties*) &props
			);
			return props;
		}

		vk::count get_queue_family_properties(type::range_of_value_type<vk::queue_family_properties> auto&& range) const {
			uint32 count = (uint32) range.size();

			vkGetPhysicalDeviceQueueFamilyProperties(
				(VkPhysicalDevice) handle,
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
		vk::queue_family_index get_first_queue_family_index_with_capabilities(Args... args) {
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
		try_enumerate_extension_properties(type::range_of_value_type<vk::extension_properties> auto&& props, vk::extension_name extension_name) const {
			uint32 count = (uint32) props.size();
			const char* name = extension_name.begin();

			vk::result result {
				(uint32) vkEnumerateDeviceExtensionProperties(
					(VkPhysicalDevice) handle,
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
			return try_get_extension_properties_count(name).template get<vk::count>();
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
			return try_view_extension_properties(count, forward<F>(f), name).template get<vk::count>();
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
			return try_view_extension_properties(forward<F>(f), name).template get<vk::result>();
		}

		elements::one_of<vk::result, vk::count>
		try_for_each_extension_properties(auto&& f) {
			return try_view_extension_properties([&](auto view) {
				for(auto props : view) f(props);
			});
		}

		template<typename F>
		vk::count for_each_extension_properties(F&& f) {
			return try_for_each_extension_properties(forward<F>(f)).template get<vk::count>();
		}

		elements::one_of<vk::result, vk::surface_capabilities>
		try_get_surface_capabilities(vk::surface surface) const {
			vk::surface_capabilities caps;
 
			vk::result result {
				(uint32) vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
					(VkPhysicalDevice) handle,
					(VkSurfaceKHR) surface.handle,
					(VkSurfaceCapabilitiesKHR*) &caps
				)
			};
			if(result.success()) return caps;
			return result;
		}

		vk::surface_capabilities get_surface_capabilities(vk::surface surface) const {
			return try_get_surface_capabilities(surface).get<vk::surface_capabilities>();
		}

		elements::one_of<vk::result, vk::count>
		try_get_surface_formats(vk::surface surface, type::range_of_value_type<vk::surface_format> auto&& formats) const {
			uint32 count = (uint32) formats.size();
 
			vk::result result {
				(uint32) vkGetPhysicalDeviceSurfaceFormatsKHR(
					(VkPhysicalDevice) handle,
					(VkSurfaceKHR) surface.handle,
					&count,
					(VkSurfaceFormatKHR*) formats.data()
				)
			};
			if(result.success()) return vk::count{ count };
			return result;
		}

		template<type::range_of_value_type<vk::surface_format> FormatsRange>
		vk::count get_surface_formats(vk::surface surface, FormatsRange&& formats) const {
			return try_get_surface_formats(surface, forward<FormatsRange>(formats)).template get<vk::count>();
		}

		elements::one_of<vk::result, vk::count>
		try_get_surface_formats_count(vk::surface surface) const {
			return try_get_surface_formats(surface, span<vk::surface_format>{ nullptr, 0 });
		}

		vk::count get_surface_formats_count(vk::surface surface) const {
			return try_get_surface_formats_count(surface).template get<vk::count>();
		}

		elements::one_of<vk::result, vk::count>
		try_view_surface_formats(vk::surface surface, vk::count count, auto&& f) const {
			vk::surface_format formats[(uint32) count];
			auto result = try_get_surface_formats(surface, span{ formats, (uint32) count });
			if(result.is_current<vk::result>()) return result;
			count = result.get<vk::count>();
			f(span{ formats, (uint32) count });
			return count;
		}

		template<typename F>
		elements::one_of<vk::result, vk::count>
		try_view_surface_formats(vk::surface surface, F&& f) const {
			auto result = try_get_surface_formats_count(surface);
			if(result.is_current<vk::result>()) return result;

			return try_view_surface_formats(
				surface,
				result.get<vk::count>(),
				forward<F>(f)
			);
		}

		template<typename F>
		vk::count view_surface_formats(vk::surface surface, F&& f) const {
			return try_view_surface_formats(surface, forward<F>(f)).template get<vk::count>();
		}

		vk::surface_format get_first_surface_format(vk::surface surface) const {
			vk::surface_format f;
			get_surface_formats(surface, span{ &f, 1 });
			return f;
		}

		elements::one_of<vk::result, vk::count>
		try_get_surface_present_modes(vk::surface surface, type::range_of_value_type<vk::present_mode> auto&& present_modes) const {
			uint32 count = (uint32) present_modes.size();

			vk::result result {
				(uint32) vkGetPhysicalDeviceSurfacePresentModesKHR(
					(VkPhysicalDevice) handle,
					(VkSurfaceKHR) surface.handle,
					&count,
					(VkPresentModeKHR*) present_modes.data()
				)
			};
			if(result.success()) return vk::count{ count };
			return result;
		}

		elements::one_of<vk::result, vk::count>
		try_get_surface_present_mode_count(vk::surface surface) const {
			return try_get_surface_present_modes(surface, span<vk::present_mode>{ nullptr, 0 });
		}

		elements::one_of<vk::result, vk::count>
		try_view_surface_present_modes(vk::surface surface, vk::count count, auto&& f) const {
			vk::present_mode present_modes[(uint32) count];
			auto result = try_get_surface_present_modes(surface, span{ present_modes, (uint32) count });
			if(result.is_current<vk::result>()) return result;

			count = result.get<vk::count>();
			f(span{ present_modes, (uint32) count});
			return count;
		}

		template<typename F>
		elements::one_of<vk::result, vk::count>
		try_view_surface_present_modes(const vk::surface& surface, F&& f) const {
			auto result = try_get_surface_present_mode_count(surface);
			if(result.is_current<vk::result>()) return result;
			return try_view_surface_present_modes(
				surface,
				result.get<vk::count>(),
				forward<F>(f)
			);
		}

		elements::one_of<vk::result, vk::count>
		try_for_each_surface_presesnt_mode(const vk::surface& surface, auto&& f) const {
			return try_view_surface_present_modes(surface, [&](auto view) {
				for(auto present_mode : view) {
					f(present_mode);
				}
			});
		}

		template<typename F>
		vk::count for_each_surface_present_mode(const vk::surface& surface, F&& f) const {
			return try_for_each_surface_presesnt_mode(surface, forward<F>(f)).template get<vk::count>();
		}
		
		elements::one_of<vk::result, bool>
		try_get_surface_support(const vk::surface& surface, vk::queue_family_index queue_family_index) const {
			uint32 supports;

			vk::result result {
				(uint32) vkGetPhysicalDeviceSurfaceSupportKHR(
					(VkPhysicalDevice) handle,
					(uint32) queue_family_index,
					(VkSurfaceKHR) surface.handle,
					&supports
				)
			};
			if(result.success()) return supports;
			return result;
		}

		bool get_surface_support(const vk::surface& surface, vk::queue_family_index queue_family_index) const {
			return try_get_surface_support(surface, queue_family_index).get<bool>();
		}
	};

}

#include "../device/create.hpp"


template<typename... Args>
vk::device vk::physical_device::create_device(Args&&... args) const {
	return vk::create_device(*this, forward<Args>(args)...);
}