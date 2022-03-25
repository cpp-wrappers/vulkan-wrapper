#pragma once

#include "../../descriptor/set/layout/handle.hpp"
#include "../../pipeline/push_constant_range.hpp"

#include <core/flag_enum.hpp>

namespace vk {

	struct pipeline_layout_create_info {
		uint32 structure_type = 30;
		const void* next = nullptr;
		uint32 flags = 0;
		uint32 descriptor_set_layout_count = 0;
		const handle<vk::descriptor_set_layout>* descriptor_set_layouts = 0;
		uint32 push_constant_range_count = 0;
		const vk::push_constant_range* push_constant_ranges = nullptr;
	};

} // vk