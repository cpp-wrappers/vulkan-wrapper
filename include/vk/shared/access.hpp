#pragma once

#include <core/flag_enum.hpp>
#include "headers.hpp"

namespace vk {

	enum class access {
		indirect_command_read = VK_ACCESS_INDIRECT_COMMAND_READ_BIT,
		index_read = VK_ACCESS_INDEX_READ_BIT,
		vertex_attribute_read = VK_ACCESS_VERTEX_ATTRIBUTE_READ_BIT,
		uniform_read = VK_ACCESS_UNIFORM_READ_BIT,
		input_attachment_read = VK_ACCESS_INPUT_ATTACHMENT_READ_BIT,
		shader_read = VK_ACCESS_SHADER_READ_BIT,
		shader_write = VK_ACCESS_SHADER_WRITE_BIT,
		color_attachment_read = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT,
		color_attachment_write = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,
		depth_stencil_attachment_read = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT,
		depth_stencil_attachment_write = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT,
		transfer_read = VK_ACCESS_TRANSFER_READ_BIT,
		transfer_write = VK_ACCESS_TRANSFER_WRITE_BIT,
		host_read = VK_ACCESS_HOST_READ_BIT,
		host_write = VK_ACCESS_HOST_WRITE_BIT,
		memory_read = VK_ACCESS_MEMORY_READ_BIT,
		memory_write = VK_ACCESS_MEMORY_WRITE_BIT,
		transform_feedback_write = VK_ACCESS_TRANSFORM_FEEDBACK_WRITE_BIT_EXT,
		transform_feedback_counter_read = VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_READ_BIT_EXT,
		transform_feedback_counter_write = VK_ACCESS_TRANSFORM_FEEDBACK_COUNTER_WRITE_BIT_EXT,
		conditional_rendering_read = VK_ACCESS_CONDITIONAL_RENDERING_READ_BIT_EXT,
		color_attachment_read_noncoherent = VK_ACCESS_COLOR_ATTACHMENT_READ_NONCOHERENT_BIT_EXT,
		acceleration_structure_read = VK_ACCESS_ACCELERATION_STRUCTURE_READ_BIT_KHR,
		acceleration_structure_write = VK_ACCESS_ACCELERATION_STRUCTURE_WRITE_BIT_KHR,
		fragment_density_map_read = VK_ACCESS_FRAGMENT_DENSITY_MAP_READ_BIT_EXT,
		fragment_shading_rate_attachment_read = VK_ACCESS_FRAGMENT_SHADING_RATE_ATTACHMENT_READ_BIT_KHR,
		command_preprocess_read = VK_ACCESS_COMMAND_PREPROCESS_READ_BIT_NV,
		command_preprocess_write = VK_ACCESS_COMMAND_PREPROCESS_WRITE_BIT_NV,
		none = VK_ACCESS_NONE_KHR,
		shading_rate_image_read = VK_ACCESS_SHADING_RATE_IMAGE_READ_BIT_NV
	};

	struct src_access : flag_enum<vk::access> {};
	struct dst_access : flag_enum<vk::access> {};

}