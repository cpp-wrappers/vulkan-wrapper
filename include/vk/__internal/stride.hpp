#pragma once

#include <integer.hpp>

namespace vk {

	class stride {
		uint32 value_;
	public:
		stride(uint32 value) : value_{ value } {}
		operator uint32() const { return value_; }
	};

}