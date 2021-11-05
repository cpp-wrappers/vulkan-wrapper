#pragma once

#include "headers.hpp"

namespace vk {
	enum class logic_op {
		clear = VK_LOGIC_OP_CLEAR,
		_and = VK_LOGIC_OP_AND,
		and_reverse = VK_LOGIC_OP_AND_REVERSE,
		copy = VK_LOGIC_OP_COPY,
		and_inverted = VK_LOGIC_OP_AND_INVERTED,
		no_op = VK_LOGIC_OP_NO_OP,
		_xor = VK_LOGIC_OP_XOR,
		_or = VK_LOGIC_OP_OR,
		nor = VK_LOGIC_OP_NOR,
		equivalent = VK_LOGIC_OP_EQUIVALENT,
		invert = VK_LOGIC_OP_INVERT,
		or_reverse = VK_LOGIC_OP_OR_REVERSE,
		copy_inverted = VK_LOGIC_OP_COPY_INVERTED,
		or_inverted = VK_LOGIC_OP_OR_INVERTED,
		nand = VK_LOGIC_OP_NAND,
		set = VK_LOGIC_OP_SET,
	};
}