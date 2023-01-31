#pragma once

#include "../__fence/handle.hpp"

namespace vk {

	struct signal_fence : handle<vk::fence> {};

} // vk