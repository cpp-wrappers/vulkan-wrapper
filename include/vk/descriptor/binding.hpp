#pragma once

#include <core/wrapper/of_integer.hpp>

namespace vk {

	struct descriptor_binding : wrapper::of_integer<uint32> {};

	struct src_binding : wrapper::of<descriptor_binding, struct src_binding_t> {};
	struct dst_binding : wrapper::of<descriptor_binding, struct dst_binding_t>{};

} // vk