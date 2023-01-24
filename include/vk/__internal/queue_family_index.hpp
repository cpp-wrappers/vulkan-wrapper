#pragma once

#include <integer.hpp>

namespace vk {

	class queue_family_index {
		uint32 value_;
	public:
		constexpr queue_family_index() : value_{} {}
		constexpr queue_family_index(uint32 value) : value_{ value } {}
		operator uint32() const { return value_; }
	};

	inline constexpr vk::queue_family_index queue_family_ignored{ ~0U };

	struct src_queue_family_index : queue_family_index {};
	struct dst_queue_family_index : queue_family_index {};

} // vk