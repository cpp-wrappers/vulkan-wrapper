#pragma once

#include <integer.hpp>

namespace vk {

	class image_index {
		uint32 value_;
	public:
		image_index(uint32 value) : value_{ value } {}
		operator uint32 () const { return value_; }
	};
	
} // vk