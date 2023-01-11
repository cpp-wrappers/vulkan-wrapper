#pragma once

#include <core/flag_enum.hpp>

namespace vk {

	enum memory_type_index : uint32 {};

	using memory_type_indices = flag_enum<vk::memory_type_index>;

} // vk