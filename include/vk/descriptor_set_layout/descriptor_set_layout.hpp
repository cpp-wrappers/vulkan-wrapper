#pragma once

#include <core/flag_enum.hpp>

#include "binding.hpp"
#include "../result.hpp"

namespace vk {

struct descriptor_set_layout {
	descriptor_set_layout() = delete;
	descriptor_set_layout(const descriptor_set_layout&) = delete;
}; // descriptor_set_layout

} // vk