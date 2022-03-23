#pragma once

#include "handle.hpp"

#include "vk/destroy_or_free.hpp"
#include "vk/instance/handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::surface> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::instance>,
			types::are_contain_one_decayed<handle<vk::surface>>
		>::for_types<Args...>
		void operator () (Args&&... args) const {
			auto& instance = elements::possibly_guarded_handle_of<vk::instance>(args...);
			auto surface = elements::decayed<handle<vk::surface>>(args...);

			vkDestroySurfaceKHR(
				(VkInstance) vk::get_handle_value(instance),
				(VkSurfaceKHR) vk::get_handle_value(surface),
				(VkAllocationCallbacks*) nullptr
			);
		}

	};

} // vk