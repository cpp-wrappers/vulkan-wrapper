#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include "../result.hpp"
#include "../device/handle.hpp"
#include "../create_or_allocate.hpp"
#include "../device/get_proc_address.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

typedef int32 (VK_PTR* PFN_vkCreateAccelerationStructureKHR)(
	handle<vk::device> device,
	const vk::acceleration_structure_create_info* create_info,
	const void* allocator,
	handle<vk::acceleration_structure>* acceleration_structure
);

namespace vk {

	template<>
	struct vk::create_t<vk::acceleration_structure> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<vk::device>,
			types::are_may_contain_decayed<
				vk::acceleration_structure_create_flags
			>,
			types::are_contain_one_decayed<vk::buffer>,
			types::are_may_contain_one_decayed<vk::memory_offset>,
			types::are_contain_one_decayed<vk::memory_size>,
			types::are_contain_one_decayed<vk::acceleration_structure_type>,
			types::are_may_contain_one_decayed<vk::device_address>
		>::for_types<Args...>
		vk::expected<handle<vk::acceleration_structure>>
		operator () (Args&&... args) const {
			auto buffer = elements::decayed<handle<vk::buffer>>(args...);

			vk::acceleration_structure_create_info ci {
				.buffer = buffer,
				.size = elements::decayed<vk::memory_size>(args...),
				.type = elements::decayed<
					vk::acceleration_structure_type
				>(args...)
			};

			if constexpr (
				types::are_contain_decayed<
					vk::acceleration_structure_create_flags
				>::for_types<Args...>
			) {
				ci.flags = elements::decayed<
					vk::acceleration_structure_create_flags
				>(args...);
			}

			if constexpr (
				types::are_contain_decayed<
					vk::memory_offset	
				>::for_types<Args...>
			) {
				ci.offset = elements::decayed<vk::memory_offset>(args...);
			}

			if constexpr (
				types::are_contain_decayed<
					vk::device_address
				>::for_types<Args...>
			) {
				ci.device_address = elements::decayed<
					vk::device_address
				>(args...);
			}

			auto device = elements::decayed<handle<vk::device>>(args...);

			handle<vk::acceleration_structure> acceleration_structure;

			auto f =
				(PFN_vkCreateAccelerationStructureKHR)
				vk::get_device_proc_address(
					device,
					"vkCreateAccelerationStructureKHR"
				);

			vk::result result {
				f(
					device,
					&ci,
					nullptr,
					&acceleration_structure
				)
			};

			if(result.error()) return result;

			return acceleration_structure;

		} // operator ()

	}; // create_t<acceleration_structure>

} // vk