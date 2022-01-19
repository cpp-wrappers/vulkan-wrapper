#pragma once

#include "../../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../../elements/possibly_guarded_handle_of.hpp"
#include "../../../object/create_or_allocate.hpp"
#include "../handle.hpp"
#include "allocate_info.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::allocate_t<vk::device_memory> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::count_of_type<vk::device_size>::equals<1>,
			types::count_of_type<vk::memory_type_index>::equals<1>
		>::for_types_of<decay<Args>...>
		vk::expected<vk::handle<vk::device_memory>>
		operator () (Args&&... args) const {
			vk::memory_allocate_info ai {
				.size = elements::of_type<vk::device_size>(args...),
				.memory_type_index = elements::of_type<vk::memory_type_index>(args...),
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