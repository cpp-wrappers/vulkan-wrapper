#pragma once

#include <core/forward.hpp>
#include <core/elements/one_of.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/elements/range_of_value_type.hpp>

#include "shared/headers.hpp"
#include "shader_module.hpp"
#include "device/create_info.hpp"
#include "device/queue_create_info.hpp"

namespace vk {

	class physical_device;
	class shader_module;

	class device {
		void* m_device;

	public:
		device(const device&) = delete;
		device(device&& other) : m_device{ other.m_device } { other.m_device = nullptr; }

		~device() {
			if(m_device != nullptr) {
				vkDestroyDevice(
					(VkDevice) m_device,
					nullptr
				);
				m_device = nullptr;
			}
		}

		template<typename... Args>
		elements::one_of<vk::result, vk::shader_module>
		try_create_shader_module(Args... args) const {
			return vk::try_create_shader_module(*this, args...);
		}

		template<typename... Args>
		vk::shader_module
		create_shader_module(Args... args) const {
			return move(try_create_shader_module(args...).template get<vk::shader_module>());
		}
	};

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::physical_device>::equals<1u>,
			types::count_of_ranges_of_value_type<vk::queue_create_info>::less_or_equals<1u>,
			types::count_of_ranges_of_value_type<vk::extension_name>::less_or_equals<1u>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::device>
	try_create_device(const Args&... args) {
		vk::device_create_info ci{};

		const vk::physical_device& physical_device = elements::of_type<const vk::physical_device&>::for_elements_of(args...);

		if constexpr(types::count_of_ranges_of_value_type<vk::queue_create_info>::equals<1u>::for_types_of<Args...>) {
			const auto& queue_create_infos = elements::range_of_value_type<vk::queue_create_info>::for_elements_of(args...);
			ci.queue_create_info_count = (uint32) queue_create_infos.size();
			ci.queue_create_infos = queue_create_infos.data();
		}
		if constexpr(types::count_of_ranges_of_value_type<vk::extension_name>::equals<1u>::for_types_of<Args...>) {
			const auto& extensions = elements::range_of_value_type<vk::extension_name>::for_elements_of(args...);
			ci.enabled_extension_count = (uint32) extensions.size();
			ci.enabled_extension_names = extensions.data();
		}

		VkDevice device;

		vk::result result {
			(uint32) vkCreateDevice(
				(VkPhysicalDevice) &physical_device,
				(VkDeviceCreateInfo*) &ci,
				nullptr,
				(VkDevice*) &device
			)
		};
		if(result.success()) return move(*((vk::device*) & device));
		return result;
	}

	template<typename... Args>
	vk::device create_device(const Args&... args) {
		return try_create_device(args...).template move<vk::device>();
	}

}