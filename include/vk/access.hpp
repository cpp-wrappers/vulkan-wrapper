#pragma once

#include <core/flag_enum.hpp>

namespace vk {

	enum class access {
		indirect_command_read                 = 0x00000001,
		index_read                            = 0x00000002,
		vertex_attribute_read                 = 0x00000004,
		uniform_read                          = 0x00000008,
		input_attachment_read                 = 0x00000010,
		shader_read                           = 0x00000020,
		shader_write                          = 0x00000040,
		color_attachment_read                 = 0x00000080,
		color_attachment_write                = 0x00000100,
		depth_stencil_attachment_read         = 0x00000200,
		depth_stencil_attachment_write        = 0x00000400,
		transfer_read                         = 0x00000800,
		transfer_write                        = 0x00001000,
		host_read                             = 0x00002000,
		host_write                            = 0x00004000,
		memory_read                           = 0x00008000,
		memory_write                          = 0x00010000,
		none                                  = 0,
		transform_feedback_write              = 0x02000000,
		transform_feedback_counter_read       = 0x04000000,
		transform_feedback_counter_write      = 0x08000000,
		conditional_rendering_read            = 0x00100000,
		color_attachment_read_noncoherent     = 0x00080000,
		acceleration_structure_read           = 0x00200000,
		acceleration_structure_write          = 0x00400000,
		fragment_density_map_read             = 0x01000000,
		fragment_shading_rate_attachment_read = 0x00800000,
		shading_rate_image_read               = 0x00800000,
		command_preprocess_read               = 0x00020000,
		command_preprocess_write              = 0x00040000
	};

	struct src_access : flag_enum<vk::access> {};
	struct dst_access : flag_enum<vk::access> {};

} // vk