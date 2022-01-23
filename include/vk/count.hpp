#pragma once

#include <core/wrapper/of_integer.hpp>

namespace vk {

	struct count : wrapper::of_integer<uint32, struct vk_count> {};

}