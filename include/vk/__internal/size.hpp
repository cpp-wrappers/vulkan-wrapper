#pragma once

#include <integer.hpp>

namespace vk {

	class size {
		uint32 value_;
	public:
		size() = default;
		size(uint32 value) : value_{ value } {}
		operator uint32() const { return value_; }
	};

}