#pragma once

#include <core/elements/of_type.hpp>
#include <core/elements/one_of.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/forward.hpp>
#include <core/type/range.hpp>
#include <core/span.hpp>
#include <vulkan/vulkan_core.h>

#include "physical_device/properties.hpp"
#include "shared/result.hpp"
#include "surface/capabilities.hpp"
#include "shared/queue_family_index.hpp"
#include "shared/count.hpp"
#include "physical_device/queue_family_properties.hpp"
#include "shared/extension_name.hpp"
#include "shared/extension_properties.hpp"
#include "surface/format.hpp"

namespace vk {

	struct device;
	struct surface;

	struct physical_device {
		physical_device() = delete;
		physical_device(const physical_device&) = delete;
		physical_device(physical_device&&) = delete;

		physical_device_properties get_properties() const {
			vk::physical_device_properties props;
			vkGetPhysicalDeviceProperties(
				(VkPhysicalDevice) this,
				(VkPhysicalDeviceProperties*) &props
			);
			return props;
		}

		vk::count get_queue_family_properties(type::range_of_value_type<vk::queue_family_properties> auto&& range) const {
			uint32 count = (uint32) range.size();

			vkGetPhysicalDeviceQueueFamilyProperties(
				(VkPhysicalDevice) this,
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
					(VkPhysicalDevice) this,
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
		try_get_surface_capabilities(const vk::surface& surface) const {
			vk::surface_capabilities caps;
 
			vk::result result {
				(uint32) vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
					(VkPhysicalDevice) this,
					*((VkSurfaceKHR*) &surface),
					(VkSurfaceCapabilitiesKHR*) &caps
				)
			};
			if(result.success()) return caps;
			return result;
		}

		vk::surface_capabilities get_surface_capabilities(vk::surface& surface) const {
			return try_get_surface_capabilities(surface).get<vk::surface_capabilities>();
		}

		elements::one_of<vk::result, vk::count>
		try_get_surface_formats(const vk::surface& s, type::range_of_value_type<vk::surface_format> auto&& formats) const {
			uint32 count = (uint32) formats.size();
 
			vk::result result {
				(uint32) vkGetPhysicalDeviceSurfaceFormatsKHR(
					(VkPhysicalDevice) this,
					*((VkSurfaceKHR*) &s),
					&count,
					(VkSurfaceFormatKHR*) formats.data()
				)
			};
			if(result.success()) return vk::count{ count };
			return result;
		}

		template<type::range_of_value_type<vk::surface_format> FormatsRange>
		vk::count get_surface_formats(const vk::surface& s, FormatsRange&& formats) const {
			return try_get_surface_formats(s, forward<FormatsRange>(formats)).template get<vk::count>();
		}

		elements::one_of<vk::result, vk::count>
		try_get_surface_formats_count(const vk::surface& surface) const {
			return try_get_surface_formats(surface, span<vk::surface_format>{ nullptr, 0 });
		}

		vk::count get_surface_formats_count(const vk::surface& surface) const {
			return try_get_surface_formats_count(surface).template get<vk::count>();
		}

		elements::one_of<vk::result, vk::count>
		try_view_surface_formats(const vk::surface& surface, vk::count count, auto&& f) const {
			vk::surface_format formats[(uint32) count];
			auto result = try_get_surface_formats(surface, span{ formats, (uint32) count });
			if(result.is_current<vk::result>()) return result;
			count = result.get<vk::count>();
			f(span{ formats, (uint32) count });
			return count;
		}

		template<typename F>
		elements::one_of<vk::result, vk::count>
		try_view_surface_formats(vk::surface& surface, F&& f) const {
			auto result = try_get_surface_formats_count(surface);
			if(result.is_current<vk::result>()) return result;

			vk::count count = result.get<vk::count>();
			return try_view_surface_formats(
				surface,
				count,
				forward<F>(f)
			);
		}

		template<typename F>
		vk::count view_surface_formats(vk::surface& surface, F&& f) const {
			return try_view_surface_formats(surface, forward<F>(f)).template get<vk::count>();
		}
		
		elements::one_of<vk::result, bool>
		try_get_surface_support(vk::queue_family_index queue_family_index, const vk::surface& s) const {
			uint32 supports;

			vk::result result {
				(uint32) vkGetPhysicalDeviceSurfaceSupportKHR(
					(VkPhysicalDevice) this,
					(uint32) queue_family_index,
					*((VkSurfaceKHR*) & s),
					&supports
				)
			};
			if(result.success()) return supports;
			return result;
		}

		bool get_surface_support(vk::queue_family_index queue_family_index, const vk::surface& s) const {
			return try_get_surface_support(queue_family_index, s).template get<bool>();
		}
	};

}