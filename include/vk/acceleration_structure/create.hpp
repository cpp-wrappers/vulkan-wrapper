#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include "vk/result.hpp"
#include "vk/device/handle.hpp"
#include "vk/create_or_allocate.hpp"
#include "vk/handle/possibly_guarded_handle_of.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::acceleration_structure> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_may_contain_decayed<vk::acceleration_structure_create_flags>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::buffer>,
			types::are_may_contain_one_decayed<vk::memory_offset>,
			types::are_contain_one_decayed<vk::memory_size>,
			types::are_contain_one_decayed<vk::acceleration_structure_type>,
			types::are_may_contain_one_decayed<vk::device_address>
		>::for_types<Args...>
		vk::expected<vk::handle<vk::acceleration_structure>>
		operator () (Args&&... args) const {
			auto& buffer = elements::vk::possibly_guarded_handle_of<vk::buffer>(args...);

			vk::acceleration_structure_create_info ci {
				.buffer = vk::get_handle(buffer),
				.size = elements::decayed<vk::memory_size>(args...),
				.type = elements::decayed<vk::acceleration_structure_type>(args...)
			};

			if constexpr(types::are_contain_decayed<vk::acceleration_structure_create_flags>::for_types<Args...>) {
				ci.flags = elements::decayed<vk::acceleration_structure_create_flags>(args...);
			}

			if constexpr(types::are_contain_decayed<vk::memory_offset>::for_types<Args...>) {
				ci.offset = elements::decayed<vk::memory_offset>(args...);
			}

			if constexpr(types::are_contain_decayed<vk::device_address>::for_types<Args...>) {
				ci.device_address = elements::decayed<vk::device_address>(args...);
			}

			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);

			vk::handle<vk::acceleration_structure> acceleration_structure;

			vk::result result {
				(int) vkCreateAccelerationStructureKHR(
					(VkDevice) vk::get_handle_value(device),
					(const VkAccelerationStructureCreateInfoKHR*) &ci,
					(const VkAllocationCallbacks*) nullptr,
					(VkAccelerationStructureKHR*) &acceleration_structure
				)
			};

			if(result.error()) return result;

			return acceleration_structure;
		}

	};

} // vk