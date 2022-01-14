#pragma once

#include "../../../objects/device/destroy.hpp"
#include "../../../object/destroy_or_free.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::command_pool> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::count_of_type<vk::handle<vk::command_pool>>::equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
		void operator () (Args&&... args) const {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);
			auto handle = elements::of_type<vk::handle<vk::command_pool>>::ignore_const::ignore_reference::for_elements_of(args...);

			vkDestroyCommandPool(
				(VkDevice) vk::get_handle_value(device),
				(VkCommandPool) vk::get_handle_value(handle),
				(VkAllocationCallbacks*) nullptr
			);
		}

	};

} // vk