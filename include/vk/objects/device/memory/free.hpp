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
			types::count_of_type<vk::handle<vk::device_memory>>::equals<1>
		>::for_types_of<decay<Args>...>
		void operator () (Args&&... args) const {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);
			auto device_memory = elements::of_type<vk::handle<vk::device_memory>>(args...);

			vkFreeMemory(
				(VkDevice) vk::get_handle_value(device),
				(VkDeviceMemory) vk::get_handle_value(device_memory),
				(VkAllocationCallbacks*) nullptr
			);
		} 

	};

} // vk