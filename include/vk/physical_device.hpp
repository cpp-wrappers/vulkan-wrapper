#pragma once

#include "core/elements/of_type.hpp"
#include "core/elements/one_of.hpp"
#include "core/elements/range_of_value_type.hpp"
#include "physical_device/properties.hpp"
#include "shared/result.hpp"
#include "surface/capabilities.hpp"
#include "shared/queue_family_index.hpp"
#include "physical_device/get_queue_family_properties.hpp"
#include "physical_device/queue_family_properties.hpp"
#include "physical_device/enumerate_extension_properties.hpp"
#include "physical_device/get_surface_formats.hpp"
#include "physical_device/get_sufrace_support.hpp"
#include "shared/extension_name.hpp"
#include "shared/extension_properties.hpp"
#include "surface/format.hpp"

#include <core/forward.hpp>
#include <core/type/range.hpp>
#include <core/span.hpp>

namespace vk {

	struct device;
	struct surface;

	class physical_device {
		vk::internal::physical_device* m_physical_device;
	public:

		physical_device() = delete;
		physical_device(const physical_device&) = delete;

		physical_device_properties get_properties() const {
			vk::physical_device_properties props;
			vkGetPhysicalDeviceProperties(
				(VkPhysicalDevice) m_physical_device,
				(VkPhysicalDeviceProperties*) &props
			);
			return props;
		}

		/* queue family properties */
		template<type::range_of_value_type<vk::queue_family_properties> Range>
		uint32 get_queue_family_properties(const Range& range) const {
			return vk::internal::get_physical_device_queue_family_properties(
				m_physical_device,
				range
			);
		}

		uint32 queue_family_properties_count() const {
			return get_queue_family_properties(span<vk::queue_family_properties>{ nullptr, 0 });
		}

		void view_queue_family_properties(uint32 count, auto&& f) const {
			vk::queue_family_properties props[count];
			count = get_queue_family_properties(span{ props, count });
			f(span{ props, count });
		}

		template<typename F>
		void view_queue_family_properties(F&& f) const {
			view_queue_family_properties(queue_family_properties_count(), forward<F>(f));
		}

		void for_each_queue_family_properties(auto&& f) const {
			view_queue_family_properties(
				[&](auto view) {
					for(auto props : view) f(props);
				}
			);
		}
		/*          */

		/* extension properties */
		template<typename... Args>
		requires requires(vk::internal::physical_device* d, const Args&... args) {
			vk::internal::enumerate_physical_device_extension_properties(d, args...);
		}
		auto enumerate_extension_properties(const Args&... args) const {
			return vk::internal::enumerate_physical_device_extension_properties(
				m_physical_device,
				args...
			);
		}

		uint32 extension_properties_count(vk::extension_name name) const {
			return enumerate_extension_properties(name, span<vk::extension_properties>{ nullptr, 0 }).count;
		}

		uint32 extension_properties_count() const {
			return enumerate_extension_properties(span<vk::extension_properties>{ nullptr, 0 }).count;
		}

		void view_extension_properties(uint32 count, vk::extension_name name, auto&& f) const {
			vk::extension_properties props[count];
			auto result = enumerate_extension_properties(name, span{ props, count });
			f(span{ props, result.count });
		}

		void view_extension_properties(uint32 count, auto&& f) const {
			vk::extension_properties props[count];
			auto result = enumerate_extension_properties(span{ props, count });
			f(span{ props, result.count });
		}

		template<typename F>
		void view_extension_properties(vk::extension_name name, F&& f) const {
			view_extension_properties(extension_properties_count(name), forward<F>(f));
		}

		template<typename F>
		void view_extension_properties(F&& f) const {
			view_extension_properties(extension_properties_count(), forward<F>(f));
		}

		void for_each_extension_properties(auto&& f) {
			view_extension_properties([&](auto view) {
				for(auto props : view) f(props);
			});
		}
		/*          */

		elements::one_of<vk::result, vk::surface_capabilities>
		try_get_surface_capabilities(vk::surface& s) const {
			vk::surface_capabilities caps;
 
			vk::result result {
				(uint32) vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
					(VkPhysicalDevice) m_physical_device,
					(VkSurfaceKHR) &s,
					(VkSurfaceCapabilitiesKHR*) &caps
				)
			};
			if(result.success()) {
				return caps;
			}
			return result;
		}

		/*bool get_surface_support(vk::queue_family_index queue_family_index, vk::surface& s) {
			uint32_t result;

			vk::throw_if_error(
				vkGetPhysicalDeviceSurfaceSupportKHR(
					(VkPhysicalDevice) this,
					(uint32) queue_family_index,
					(VkSurfaceKHR) &s,
					&result
				)
			);

			return result;
		}*/

		/* surface formats */
		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::count_of_type<vk::surface>::equals<1>,
				types::count_of_ranges_of_value_type<vk::surface_format>::equals<1>
			>::for_types_of<Args...>
		)
		auto get_surface_formats(const Args&... args) const {
			return vk::internal::get_physical_device_surface_formats(
				(vk::internal::physical_device&) *this,
				(vk::internal::surface&) elements::of_type<const vk::surface&>::for_elements_of(args...),
				elements::range_of_value_type<vk::surface_format>::for_elements_of(args...)
			);
		}

		uint32 surface_formats_count(const vk::surface& surface) const {
			return get_surface_formats(surface, span<vk::surface_format>{ nullptr, 0 }).count;
		}

		void view_surface_formats(const vk::surface& surface, uint32 count, auto&& f) const {
			vk::surface_format formats[count];
			auto result = get_surface_formats(surface, span{ formats, count });
			return f(span{ formats, result.count });
		}

		template<typename F>
		void view_surface_formats(vk::surface& surface, F&& f) const {
			view_surface_formats(surface, surface_formats_count(surface), forward<F>(f));
		}
		/*          */
	};

}