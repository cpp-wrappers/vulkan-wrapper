#pragma once

#include <core/wrapper/of.hpp>

#include "vk/semaphore/handle.hpp"

namespace vk {

	struct wait_semaphore : wrapper::of<handle<vk::semaphore>, struct wait_semaphore_t> {};

}