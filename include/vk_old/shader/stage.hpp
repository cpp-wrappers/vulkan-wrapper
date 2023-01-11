#pragma once

#include <core/flag_enum.hpp>

namespace vk {

	enum class shader_stage {
		vertex                  = 0x00000001,
		tessellation_control    = 0x00000002,
		tessellation_evaluation = 0x00000004,
		geometry                = 0x00000008,
		fragment                = 0x00000010,
		compute                 = 0x00000020,
		all_graphics            = 0x0000001F,
		all                     = 0x7FFFFFFF,
		raygen                  = 0x00000100,
		any_hit                 = 0x00000200,
		closest_hit             = 0x00000400,
		miss                    = 0x00000800,
		intersection            = 0x00001000,
		callable                = 0x00002000,
		task                    = 0x00000040,
		mesh                    = 0x00000080,
		subpass_shading         = 0x00004000
	};

	using shader_stages = flag_enum<vk::shader_stage>;

} // vk