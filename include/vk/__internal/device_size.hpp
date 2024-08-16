#pragma once

#include <integer.hpp>

namespace vk {

	class device_size {
		uint64 value_;
	public:
		constexpr device_size() = default;
		constexpr device_size(uint64 value) : value_{ value } {}
		explicit operator uint64& () { return value_; }
		explicit operator const uint64& () const { return value_; }
	};

} // vk