#pragma once

namespace vk {

	enum class logic_op {
		clear         = 0,
		_and          = 1,
		and_reverse   = 2,
		copy          = 3,
		and_inverted  = 4,
		no_op         = 5,
		_xor          = 6,
		_or           = 7,
		nor           = 8,
		equivalent    = 9,
		invert        = 10,
		or_reverse    = 11,
		copy_inverted = 12,
		or_inverted   = 13,
		nand          = 14,
		set           = 15,
	};

} // vk