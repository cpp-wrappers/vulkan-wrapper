#pragma once

#include "vk/headers.hpp"

namespace vk {

	enum class descriptor_type {
		sampler = VK_DESCRIPTOR_TYPE_SAMPLER,
		combined_image_sampler = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
		sampled_image = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,
		storage_image = VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,
		uniform_texel_buffer = VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,
		storage_texel_buffer = VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,
		uniform_buffer = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
		storage_buffer = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
		uniform_buffer_dynamic = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC,
		storage_buffer_dynamic = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC,
		input_attachment = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,
		inline_uniform_block_ext = VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK_EXT,
		acceleration_structure_khr = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_KHR,
		acceleration_structure_nv = VK_DESCRIPTOR_TYPE_ACCELERATION_STRUCTURE_NV,
		//mutable_valve = VK_DESCRIPTOR_TYPE_MUTABLE_VALVE,
	};

} // vk