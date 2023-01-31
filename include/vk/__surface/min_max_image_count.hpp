#pragma once

#include <integer.hpp>

namespace vk {

	class min_image_count {
		uint32 value_;
	public:
		min_image_count() = default;
		min_image_count(uint32 value) : value_{ value } {}
		operator uint32() const { return value_; }
	};

	class max_image_count {
		uint32 value_;
	public:
		max_image_count() = default;
		max_image_count(uint32 value) : value_{ value } {}
		operator uint32() const { return value_; }
	};

} // vk