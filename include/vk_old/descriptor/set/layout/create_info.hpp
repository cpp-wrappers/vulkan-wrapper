#pragma once

#include "binding.hpp"

#include <core/integer.hpp>
#include <core/flag_enum.hpp>

namespace vk {

	enum class descriptor_set_layout_create_flag {
		update_after_bind_pool = 0x00000002,
		push_descriptor        = 0x00000001,
		host_only_pool         = 0x00000004
	};

	using descriptor_set_layout_create_flags = flag_enum<
		vk::descriptor_set_layout_create_flag
	>;

	struct descriptor_set_layout_create_info {
		uint32                                   structure_type = 32;
		const void*                              next = nullptr;
		vk::descriptor_set_layout_create_flags   flags;
		uint32                                   binding_count = 0;
		const vk::descriptor_set_layout_binding* bindings = nullptr;
	};

} // vk