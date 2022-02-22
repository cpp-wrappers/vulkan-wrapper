#pragma once

#include <core/flag_enum.hpp>

#include "headers.hpp"

namespace vk {
	enum class color_component {
		r = VK_COLOR_COMPONENT_R_BIT,
		g = VK_COLOR_COMPONENT_G_BIT,
		b = VK_COLOR_COMPONENT_B_BIT,
		a = VK_COLOR_COMPONENT_A_BIT
	};

	using color_components = flag_enum<vk::color_component>;

} // vk
