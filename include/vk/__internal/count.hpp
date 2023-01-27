#pragma once

#include <integer.hpp>

namespace vk {

	class count {
		uint32 value_;
	public:
		count() = default;
		count(uint32 value) : value_{ value } {}
		operator uint32 () const { return value_; }
	};

} // vk