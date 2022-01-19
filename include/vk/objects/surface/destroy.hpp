#pragma once

#include "../../object/destroy_or_free.hpp"
#include "../instance/handle.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::surface> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::instance>,
			types::count_of_type<vk::handle<vk::surface>>::equals<1>
		>::for_types_of<decay<Args>...>
		void operator () (Args&&... args) const {
			auto& instance = elements::vk::possibly_guarded_handle_of<vk::instance>(args...);
			auto surface = elements::of_type<vk::handle<vk::surface>>(args...);

			vkDestroySurfaceKHR(
				(VkInstance) vk::get_handle_value(instance),
				(VkSurfaceKHR) vk::get_handle_value(surface),
				(VkAllocationCallbacks*) nullptr
			);
		}

	};

} // vk