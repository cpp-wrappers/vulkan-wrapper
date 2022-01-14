#pragma once

#include "../type.hpp"
#include "../count.hpp"

namespace vk {

	struct descriptor_pool_size {
		vk::descriptor_type type;
		vk::descriptor_count descriptor_count;
	};

} // vk