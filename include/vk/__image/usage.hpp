#pragma once

#include <enum_flags.hpp>

namespace vk {

	enum class image_usage {
		transfer_src                     = 0x00000001,
		transfer_dst                     = 0x00000002,
		sampled                          = 0x00000004,
		storage                          = 0x00000008,
		color_attachment                 = 0x00000010,
		depth_stencil_attachment         = 0x00000020,
		transient_attachment             = 0x00000040,
		input_attachment                 = 0x00000080,
		fragment_density_map             = 0x00000200,
		fragment_shading_rate_attachment = 0x00000100,
		invocation_mask                  = 0x00040000
	};

	using image_usages = enum_flags<vk::image_usage>;

} // vk