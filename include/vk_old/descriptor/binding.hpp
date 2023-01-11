#pragma once

#include <core/integer.hpp>

namespace vk {

	struct descriptor_binding { uint32 _; };

	struct src_binding : descriptor_binding {};
	struct dst_binding : descriptor_binding {};

} // vk