#pragma once

#include "./handle.hpp"

#include "../__internal/function.hpp"

#include <body.hpp>

namespace vk {

	struct destroy_instance_function : vk::function<void(*)(
		handle<vk::instance> instance,
		const void* allocator
	)> {
		static constexpr auto name = "vkDestroyInstance";
	};

	inline void destroy_instance(handle<vk::instance> instance) {
		vk::get_instance_function<vk::destroy_instance_function>(
			instance
		)(
			instance,
			nullptr
		);	
	}

}

template<>
inline void body<vk::instance>::do_destroy() {
	vk::destroy_instance(this->handle());
};