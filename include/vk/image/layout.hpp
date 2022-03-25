#pragma once

#include <core/wrapper/of.hpp>

namespace vk {

	enum class image_layout {
		undefined                                  = 0,
		general                                    = 1,
		color_attachment_optimal                   = 2,
		depth_stencil_attachment_optimal           = 3,
		depth_stencil_read_only_optimal            = 4,
		shader_read_only_optimal                   = 5,
		transfer_src_optimal                       = 6,
		transfer_dst_optimal                       = 7,
		preinitialized                             = 8,
		depth_read_only_stencil_attachment_optimal = 1000117000,
		depth_attachment_stencil_read_only_optimal = 1000117001,
		depth_attachment_optimal                   = 1000241002,
		depth_read_only_optimal                    = 1000117003,
		stencil_attachment_optimal                 = 1000117004,
		stencil_read_only_optimal                  = 1000117005,
		read_only_optimal                          = 1000314000,
		attachment_optimal                         = 1000314001,
		present_src                                = 1000001002,
		shared_present                             = 1000111000,
		fragment_density_map_optimal               = 1000218000,
		fragment_shading_rate_attachment_optimal   = 1000164003
	};

	struct initial_layout : wrapper::of<vk::image_layout> {};
	struct final_layout : wrapper::of<vk::image_layout> {};

} // vk