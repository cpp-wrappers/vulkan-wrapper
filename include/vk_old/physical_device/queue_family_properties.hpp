#pragma once

#include "../extent.hpp"

#include <core/flag_enum.hpp>

namespace vk {

	enum class queue_flag {
		graphics       = 0x00000001,
		compute        = 0x00000002,
		transfer       = 0x00000004,
		sparse_binding = 0x00000008,
		_protected     = 0x00000010
	};

	struct queue_family_properties {
		flag_enum<queue_flag> flags;
		uint32 count;
		uint32 timestamp_valid_bits;
		vk::extent<3> min_image_transfer_granularity;
	};

} // vk