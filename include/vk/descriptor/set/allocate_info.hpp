#pragma once

#include "layout/handle.hpp"

#include "../../count.hpp"
#include "../../descriptor/pool/handle.hpp"

namespace vk {

	struct descriptor_set_allocate_info {
		uint32 structyre_type = 34;
		const void* next;
		handle<vk::descriptor_pool> descriptor_pool;
		vk::count descriptor_set_count;
		const handle<vk::descriptor_set_layout>* descriptor_set_layouts;
	};

} // vk