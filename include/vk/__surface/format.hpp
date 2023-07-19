#pragma once

#include "../__internal/format.hpp"
#include "../__image/color_space.hpp"

namespace vk {

	struct surface_format {
		vk::format format;
		vk::color_space color_space;

		bool operator == (surface_format other) const {
			return format == other.format && color_space == other.color_space;
		}
	};

} // vk