#pragma once

#include "size.hpp"

#include <core/wrapper/of_integer.hpp>
#include <core/flag_enum.hpp>

namespace vk {

	enum class descriptor_pool_create_flag {
		free_descriptor_set_bit = 0x00000001,
		update_after_bind_bit   = 0x00000002,
		host_only_bit_valve     = 0x00000004
	};

	using descriptor_pool_create_flags =
		flag_enum<vk::descriptor_pool_create_flag>;

	struct max_sets : wrapper::of_integer<uint32, struct max_sets_t> {};

	struct descriptor_pool_create_info {
		uint32 structure_type = 33;
		const void* next;
		vk::descriptor_pool_create_flags flags;
		vk::max_sets max_sets;
		uint32 pool_size_count;
		const vk::descriptor_pool_size* pool_sizes;
	};

} // vk