#pragma once

#include <core/wrapper/of_integer.hpp>

namespace vk {

	struct first_binding :
		wrapper::of_integer<uint32, struct first_binding_t>
	{};

} // vk