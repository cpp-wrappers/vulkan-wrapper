#pragma once

#include <core/exchange.hpp>

#include "handle.hpp"
#include "../instance/handle.hpp"
#include "../shared/guarded.hpp"

namespace vk {
	struct instance;

	template<>
	class guarded<vk::surface> {
		vk::surface surface;
		vk::instance instance;
	public:

		guarded<vk::surface>(vk::surface surface, vk::instance instance)
			: surface{ surface }, instance{ instance }
		{}

		~guarded() {
			if(surface.handle) {
				vkDestroySurfaceKHR(
					(VkInstance) instance.handle,
					(VkSurfaceKHR) exchange(surface.handle, 0),
					nullptr
				);
			}
		}

		const vk::surface& object() const {
			return surface;
		}
	};
}