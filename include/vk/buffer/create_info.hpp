#pragma once

#include "../sharing_mode.hpp"
#include "../queue_family_index.hpp"
#include "../device_size.hpp"

#include <core/integer.hpp>
#include <core/flag_enum.hpp>

namespace vk {

	enum class buffer_create_flag {
		sparse_binding                = 0x00000001,
		sparse_residency              = 0x00000002,
		sparse_aliased                = 0x00000004,
		_protected                    = 0x00000008,
		device_address_capture_replay = 0x00000010
	};

	enum class buffer_usage {
		transfer_src                                 = 0x00000001,
		transfer_dst                                 = 0x00000002,
		uniform_texel_buffer                         = 0x00000004,
		storage_texel_buffer                         = 0x00000008,
		uniform_buffer                               = 0x00000010,
		storage_buffer                               = 0x00000020,
		index_buffer                                 = 0x00000040,
		vertex_buffer                                = 0x00000080,
		indirect_buffer                              = 0x00000100,
		shader_device_address                        = 0x00020000,
		transform_feedback_buffer                    = 0x00000800,
		transform_feedback_counter_buffer            = 0x00001000,
		conditional_rendering                        = 0x00000200,
		acceleration_structure_build_input_read_only = 0x00080000,
		acceleration_structure_storage               = 0x00100000,
		shader_binding_table                         = 0x00000400
	};

	using buffer_create_flags = flag_enum<vk::buffer_create_flag>;
	using buffer_usages = flag_enum<vk::buffer_usage>;
	using buffer_size = vk::device_size;

	struct buffer_create_info {
		uint32 structure_type = 12;
		const void* next = nullptr;
		vk::buffer_create_flags flags;
		vk::buffer_size size;
		vk::buffer_usages usage;
		vk::sharing_mode sharing_mode;
		uint32 queue_family_index_count = 0;
		const vk::queue_family_index* queue_fanily_indices = nullptr;
	};

} // vk