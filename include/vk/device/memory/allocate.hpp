#pragma once

#include "handle.hpp"
#include "allocate_info.hpp"
#include "allocate_flags_info.hpp"
#include "../../device/handle.hpp"
#include "../../create_or_allocate.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/types/are_contain_satisfying_predicate.hpp>
#include <core/handle/possibly_guarded_of.hpp>

namespace vk {

	template<>
	struct vk::allocate_t<vk::device_memory> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_contain_one_decayed<vk::memory_size>,
			types::are_contain_one_decayed<vk::memory_type_index>,
			types::are_may_contain_decayed<vk::memory_allocate_flags_info>
		>::for_types<Args...>
		vk::expected<handle<vk::device_memory>>
		operator () (Args&&... args) const {
			vk::memory_allocate_info ai {
				.size = elements::decayed<vk::memory_size>(args...),
				.memory_type_index {
					elements::decayed<vk::memory_type_index>(args...)
				}
			};

			if constexpr (
				types::are_contain_decayed<
					vk::memory_allocate_flags_info
				>::for_types<Args...>
			) {
				ai.next = &elements::decayed<
					vk::memory_allocate_flags_info
				>(args...);
			}

			auto& device = elements::possibly_guarded_handle_of<
				vk::device
			>(args...);

			handle<vk::device_memory> device_memory;

			vk::result result {
				(int32) vkAllocateMemory(
					(VkDevice) vk::get_handle_value(device),
					(VkMemoryAllocateInfo*) &ai,
					(VkAllocationCallbacks*) nullptr,
					(VkDeviceMemory*) &device_memory
				)
			};

			if(result.error()) return result;

			return device_memory;

		} // operator ()

	}; // allocate_t<device_memory>

} // vk