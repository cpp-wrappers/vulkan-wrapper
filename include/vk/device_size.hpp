#pragma once

#include <core/wrapper/of_integer.hpp>

namespace vk {

	struct device_size : wrapper::of_integer<uint64, struct device_size_t> {};

} // vk