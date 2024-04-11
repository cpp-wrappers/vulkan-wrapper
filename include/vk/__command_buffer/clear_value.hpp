#pragma once

#include <integer.hpp>

namespace vk {

	struct clear_color_value {
		float r, g, b, a;

		clear_color_value(float r, float g, float b, float a) :
			r { r }, g { g }, b { b }, a { a }
		{}
	};

	struct clear_depth_stencil_value {
		float depth{};
		uint32 stencil{};
	};

	union clear_value {
		clear_color_value color;
		clear_depth_stencil_value depth_stencil;
	};

} // vk