#pragma once

#include <core/exchange.hpp>

#include "handle.hpp"
#include "../instance/handle.hpp"

namespace vk {
	class instance;

	class surface_guard {
		vk::surface surface;
		vk::instance instance;
	public:

		surface_guard(vk::surface surface, vk::instance instance)
			: surface{ surface }, instance{ instance }
		{}

		~surface_guard() {
			if(surface.handle) {
				vkDestroySurfaceKHR(
					(VkInstance) instance.handle,
					(VkSurfaceKHR) exchange(surface.handle, 0),
					nullptr
				);
			}
		}

		vk::surface object() const {
			return surface;
		}
	};
}