#pragma once

#include "shared/headers.hpp"

namespace vk {
	class instance;

	class surface {
		void* m_surface;
		vk::instance& m_instance;

	public:
		surface(const surface&) = delete;
		surface(void* raw_handle, vk::instance& instance)
			: m_surface{ raw_handle }, m_instance( instance )
		{}

		~surface() {
			if(m_surface) {
				vkDestroySurfaceKHR(
					*((VkInstance*) &m_instance),
					(VkSurfaceKHR) m_surface,
					nullptr
				);
				m_surface = nullptr;
			}
		}

	}; // surface

} // vk