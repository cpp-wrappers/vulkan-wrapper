#pragma once

#include <core/flag_enum.hpp>

namespace vk {

	enum class image_aspect {
		none           = 0,
		color          = 0x00000001,
		depth          = 0x00000002,
		stencil        = 0x00000004,
		metadata       = 0x00000008,
		plane_0        = 0x00000010,
		plane_1        = 0x00000020,
		plane_2        = 0x00000040,
		memory_plane_0 = 0x00000080,
		memory_plane_1 = 0x00000100,
		memory_plane_2 = 0x00000200,
		memory_plane_3 = 0x00000400
	};

	using image_aspects = flag_enum<vk::image_aspect>;

} // vk