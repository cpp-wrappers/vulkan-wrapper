#pragma once

#include "../../shared/create_or_allocate.hpp"
#include "../handle.hpp"
#include "allocate_info.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::allocate_t<vk::device_memory> {

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::vk::contain_one<vk::device>,
				types::count_of_type<vk::device_size>::equals<1>::ignore_const::ignore_reference,
				types::count_of_type<vk::memory_type_index>::equals<1>::ignore_const::ignore_reference
			>::for_types_of<Args...>
		)
		vk::expected<vk::handle<vk::device_memory>>
		operator () (Args&&... args) const {
			vk::memory_allocate_info ai {
				.size = elements::of_type<vk::device_size>::ignore_const::ignore_reference::for_elements_of(args...),
				.memory_type_index = elements::of_type<vk::memory_type_index>::ignore_const::ignore_reference::for_elements_of(args...),
			};

			auto& device = elements::vk::of_type<vk::device>::for_elements_of(args...);

			VkDeviceMemory device_memory;

			vk::result result {
				(int32) vkAllocateMemory(
					(VkDevice) vk::get_handle_value(device),
					(VkMemoryAllocateInfo*) &ai,
					(VkAllocationCallbacks*) nullptr,
					&device_memory
				)
			};

			if(result.success()) return vk::handle<vk::device_memory>{ device_memory };

			return result;
		}
	};

} // vk