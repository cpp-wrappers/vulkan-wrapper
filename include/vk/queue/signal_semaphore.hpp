#pragma once

#include <core/wrapper/of.hpp>

#include "../semaphore/handle.hpp"

namespace vk {
	struct signal_semaphore : wrapper::of<vk::handle<vk::semaphore>, struct signal_semaphore_t> {};
}