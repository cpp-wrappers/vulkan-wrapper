#pragma once

#include <core/wrapper/of_integer.hpp>

namespace vk {
	struct descriptor_count : wrapper::of_integer<uint32, struct descriptor_count_t> {};
}