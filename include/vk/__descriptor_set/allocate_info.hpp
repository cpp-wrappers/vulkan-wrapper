#pragma once

#include "../__descriptor_set_layout/handle.hpp"
#include "../__descriptor_pool/handle.hpp"
#include "../__internal/count.hpp"

namespace vk {

	struct descriptor_set_allocate_info {
		uint32 structyre_type = 34;
		const void* next = nullptr;
		handle<vk::descriptor_pool>::underlying_type descriptor_pool;
		vk::count descriptor_set_count;
		const handle<vk::descriptor_set_layout>::underlying_type*
			descriptor_set_layouts;
	};

} // vk