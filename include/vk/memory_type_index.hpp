#pragma once

#include <core/wrapper/of_integer.hpp>
#include <core/flag_enum.hpp>

namespace vk {

	enum memory_type_index : uint32 {};

	using memory_type_indices = flag_enum<vk::memory_type_index>;

} // vk