#pragma once

#include "../handle.hpp"
#include "../queue_family_properties.hpp"
#include "../../__instance/handle.hpp"
#include "../../__internal/function.hpp"

#include <integer.hpp>
#include <types.hpp>

namespace vk {

	struct get_physical_device_queue_family_properties_function :
		vk::function<void(*)(
			vk::physical_device*         physical_device,
			uint32*                      queue_family_property_count,
			vk::queue_family_properties* queue_family_properties
		)>
	{
		static constexpr auto name = "vkGetPhysicalDeviceQueueFamilyProperties";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::physical_device>> == 1,
		count_of_range_of_decayed<vk::queue_family_properties> == 1
	>
	[[ nodiscard ]]
	uint32 get_physical_device_queue_family_properties(Args&&... args) {
		handle<vk::instance> instance = tuple{ args... }.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::physical_device> physical_device = tuple{ args... }.template
			get_decayed_same_as<handle<vk::physical_device>>();

		auto& range = tuple{ args... }.template
			get_range_of_decayed<vk::queue_family_properties>();

		uint32 count = (uint32) range.size();

		vk::get_instance_function<
			vk::get_physical_device_queue_family_properties_function
		>(instance)(
			physical_device.underlying(),
			&count,
			range.iterator()
		);

		return count;
	}

} // vk