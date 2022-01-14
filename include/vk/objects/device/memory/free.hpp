#pragma once

#include "../../../object/destroy_or_free.hpp"
#include "../handle.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::free_t<vk::device_memory> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::count_of_type<vk::handle<vk::device_memory>>::equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
		void operator () (Args&&... args) const {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);
			auto device_memory = elements::of_type<vk::handle<vk::device_memory>>::ignore_const::ignore_reference::for_elements_of(args...);

			vkFreeMemory(
				(VkDevice) vk::get_handle_value(device),
				(VkDeviceMemory) vk::get_handle_value(device_memory),
				(VkAllocationCallbacks*) nullptr
			);
		} 

	};

} // vk