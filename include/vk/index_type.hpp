#pragma once

#include "vk/headers.hpp"

namespace vk {

	enum class index_type {
		uint16 = VK_INDEX_TYPE_UINT16,
		uint32 = VK_INDEX_TYPE_UINT32,
		none = VK_INDEX_TYPE_NONE_KHR,
		uint8 = VK_INDEX_TYPE_UINT8_EXT
	};

}