#pragma once

#include "handle.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

#include "vk/device/handle.hpp"
#include <core/handle/possibly_guarded_of.hpp>
#include "vk/destroy_or_free.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::acceleration_structure> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_contain_one_decayed<handle<vk::acceleration_structure>>
		>::template for_types<Args...>
		void operator () (Args&&... args) const {
			auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);

			auto f = (PFN_vkDestroyAccelerationStructureKHR) vkGetDeviceProcAddr(
				(VkDevice) vk::get_handle_value(device),
				"vkDestroyAccelerationStructureKHR"
			);

			auto acceleration_structure = elements::decayed<handle<vk::acceleration_structure>>(args...);

			f(
				(VkDevice) vk::get_handle_value(device),
				(VkAccelerationStructureKHR) vk::get_handle_value(acceleration_structure),
				(VkAllocationCallbacks*) nullptr
			);
		}

	};

} // vk