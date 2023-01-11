#pragma once

#include "./handle.hpp"

#include "../__internal/function.hpp"

#include <body.hpp>

/*extern "C" VK_ATTR void VK_CALL vkDestroyInstance(
	handle<vk::instance> instance,
	const void*          allocator
);*/

namespace vk {

	struct destroy_instance_function : vk::function<void(*)(
		vk::instance*  instance,
		const void*    allocator
	)> {
		static constexpr auto name = "vkDestroyInstance";
	};

}

template<>
inline void body<vk::instance>::do_destroy() {
	vk::get_instance_function<vk::destroy_instance_function>(
		this->soul_handle_
	)(
		this->soul_handle_.underlying(),
		nullptr
	);
};