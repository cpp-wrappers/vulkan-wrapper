#pragma once

#include "image_index.hpp"

#include "../semaphore/handle.hpp"
#include "../fence/handle.hpp"
#include "../timeout.hpp"
#include "../result.hpp"
#include "../count.hpp"
#include "../image/handle.hpp"
#include "../create_or_allocate.hpp"

#include <core/span.hpp>
#include <core/forward.hpp>
#include <core/exchange.hpp>
#include <core/range_of_value_type_same_as.hpp>
#include <core/meta/decayed_same_as.hpp>

namespace vk {

	struct semaphore;
	struct fence;
	struct image;
	struct device;
	struct swapchain;

	template<>
	inline constexpr bool is_creatable<vk::swapchain> = true;

} // vk

template<>
struct handle<vk::swapchain> : vk::handle_base<vk::non_dispatchable> {
}; // handle<swapchain>