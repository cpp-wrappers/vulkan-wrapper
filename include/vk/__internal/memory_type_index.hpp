#pragma once

#include <enum_flags.hpp>

namespace vk {

	enum memory_type_index : uint32 {};

	using memory_type_indices = enum_flags<vk::memory_type_index>;

} // vk