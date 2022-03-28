#pragma once

#include "handle.hpp"

#include "../destroy_or_free.hpp"
#include "../instance/handle.hpp"
#include "../function.hpp"

extern "C" VK_ATTR void VK_CALL vkDestroySurfaceKHR(
	handle<vk::instance> instance,
	handle<vk::surface> surface,
	const void* allocator
);

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
				vk::get_handle(instance),
				vk::get_handle(surface),
				nullptr
			);
		}

	};

} // vk