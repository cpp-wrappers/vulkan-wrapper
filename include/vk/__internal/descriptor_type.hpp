#pragma once

namespace vk {

	enum class descriptor_type {
		sampler                   = 0,
		combined_image_sampler    = 1,
		sampled_image             = 2,
		storage_image             = 3,
		uniform_texel_buffer      = 4,
		storage_texel_buffer      = 5,
		uniform_buffer            = 6,
		storage_buffer            = 7,
		uniform_buffer_dynamic    = 8,
		storage_buffer_dynamic    = 9,
		input_attachment          = 10,
		inline_uniform_block      = 1000138000,
		acceleration_structure    = 1000150000,
		acceleration_structure_nv = 1000165000,
		mutable_valve             = 1000351000,
	};

} // vk