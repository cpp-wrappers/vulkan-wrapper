#pragma once

#include <integer.hpp>

namespace vk {

	class timeout {
		uint64 value_;
	public:
		timeout(uint64 value) : value_ { value } {}
		operator uint64 () const { return value_; }
	};

} // vk