#pragma once

#include "handle.hpp"
#include "allocate_info.hpp"
#include "../handle.hpp"
#include "../../create_or_allocate.hpp"
#include "../../handle/possibly_guarded_handle_of.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/meta/types/are_contain_satisfying_predicate.hpp>

namespace vk {

	template<>
	struct vk::allocate_t<vk::device_memory> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_contain_one_decayed<vk::memory_size>,
			types::are_contain_one_decayed<vk::memory_type_index>
		>::for_types<Args...>
		vk::expected<vk::handle<vk::device_memory>>
		operator () (Args&&... args) const {
			vk::memory_allocate_info ai {
				.size = elements::decayed<vk::memory_size>(args...),
				.memory_type_index = elements::decayed<vk::memory_type_index>(args...),
			};

			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);

			vk::handle<vk::device_memory> device_memory;

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
		}

	};

} // vk