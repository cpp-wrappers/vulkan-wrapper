#pragma once

#include "../../object/destroy_or_free.hpp"
#include "../device/handle.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::fence> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::count_of_type<vk::handle<vk::fence>>::equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
		void operator() (Args&&... args) const {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);
			auto fence = elements::of_type<vk::handle<vk::fence>>::ignore_const::ignore_reference::for_elements_of(args...);

			vkDestroyFence(
				(VkDevice) vk::get_handle_value(device),
				(VkFence) vk::get_handle_value(fence),
				(VkAllocationCallbacks*) nullptr
			);
		}
	};

} // vk