#pragma once

#include <core/wrapper/of.hpp>

#include "vk/semaphore/handle.hpp"

namespace vk {

	struct signal_semaphore : wrapper::of<handle<vk::semaphore>, struct signal_semaphore_t> {};

} // vk