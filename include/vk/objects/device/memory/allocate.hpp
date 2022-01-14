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
			types::count_of_type<vk::device_size>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::memory_type_index>::equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
		vk::expected<vk::handle<vk::device_memory>>
		operator () (Args&&... args) const {
			vk::memory_allocate_info ai {
				.size = elements::of_type<vk::device_size>::ignore_const::ignore_reference::for_elements_of(args...),
				.memory_type_index = elements::of_type<vk::memory_type_index>::ignore_const::ignore_reference::for_elements_of(args...),
			};

			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);

			VkDeviceMemory device_memory;

			vk::result result {
				(int32) vkAllocateMemory(
					(VkDevice) vk::get_handle_value(device),
					(VkMemoryAllocateInfo*) &ai,
					(VkAllocationCallbacks*) nullptr,
					&device_memory
				)
			};

			if(result.error()) return result;

			return vk::handle<vk::device_memory>{ device_memory };
		}
	};

} // vk