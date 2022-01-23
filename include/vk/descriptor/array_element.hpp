#pragma once

#include <core/wrapper/of_integer.hpp>

namespace vk {

	struct descriptor_array_element : wrapper::of_integer<uint32> {};

	struct src_array_element : wrapper::of<descriptor_array_element, struct src_array_element_t> {};
	struct dst_array_element : wrapper::of<descriptor_array_element, struct dst_array_element_t>{};

} // vk