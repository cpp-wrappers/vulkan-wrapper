#pragma once

#include "../__internal/format.hpp"
#include "../__image/color_space.hpp"

namespace vk {

	struct surface_format {
		vk::format format;
		vk::color_space color_space;
	};

} // vk