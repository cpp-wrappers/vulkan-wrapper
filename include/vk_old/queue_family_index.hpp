#pragma once

#include <core/integer.hpp>

namespace vk {

	struct queue_family_index {
		uint32 _;

		operator uint32 () const { return _; }
	};

	inline constexpr vk::queue_family_index queue_family_ignored{ ~0U };

	struct src_queue_family_index : queue_family_index {};
	struct dst_queue_family_index : queue_family_index {};

} // vk