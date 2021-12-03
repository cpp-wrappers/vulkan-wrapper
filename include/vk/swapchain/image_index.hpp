#pragma once

#include <core/wrapper/of_integer.hpp>

namespace vk {

	struct image_index : wrapper::of_integer<uint32, struct vk_image_index> {};
	
}