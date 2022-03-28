#pragma once

#include "handle.hpp"

#include "../device/get_proc_address.hpp"
#include "../device/handle.hpp"
#include "../destroy_or_free.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/handle/possibly_guarded_of.hpp>

typedef void (VK_PTR* PFN_vkDestroyAccelerationStructureKHR)(
	handle<vk::device> device,
	handle<vk::acceleration_structure> acceleration_structure,
	const void* allocator
);

namespace vk {

	template<>
	struct vk::destroy_t<vk::acceleration_structure> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_contain_one_decayed<handle<vk::acceleration_structure>>
		>::template for_types<Args...>
		void operator () (Args&&... args) const {
			auto& device = elements::possibly_guarded_handle_of<
				vk::device
			>(args...);

			auto f =
				(PFN_vkDestroyAccelerationStructureKHR)
				vk::get_device_proc_address(
					device,
					"vkDestroyAccelerationStructureKHR"
				);

			auto acceleration_structure = elements::decayed<
				handle<vk::acceleration_structure>
			>(args...);

			f(
				vk::get_handle(device),
				vk::get_handle(acceleration_structure),
				nullptr
			);
		}

	};

} // vk