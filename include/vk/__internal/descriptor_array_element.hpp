#pragma once

#include <integer.hpp>

namespace vk {

	struct descriptor_array_element { uint32 _; };
	struct src_array_element : descriptor_array_element {};
	struct dst_array_element : descriptor_array_element {};

} // vk