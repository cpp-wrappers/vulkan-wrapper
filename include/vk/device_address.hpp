#pragma once

#include <core/wrapper/of_integer.hpp>

namespace vk {

	struct device_address : wrapper::of_integer<uint64, struct device_address_t> {};

} // vk