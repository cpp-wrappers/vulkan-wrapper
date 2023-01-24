#pragma once

#include "./handle.hpp"

#include "../__internal/function.hpp"

namespace vk {

	struct destroy_surface_function : vk::function<void(*)(
		handle<vk::instance>::underlying_type,
		handle<vk::surface>::underlying_type,
		const void*
	)> {
		static constexpr auto name = "vkDestroySurfaceKHR";
	};

	inline void destroy_surface(
		handle<vk::instance> instance,
		handle<vk::surface> surface
	) {
		vk::get_instance_function<destroy_surface_function>(instance)(
			instance.underlying(), surface.underlying(), nullptr
		);
	}

}