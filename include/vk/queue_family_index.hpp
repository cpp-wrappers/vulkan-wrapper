#pragma once

#include <core/wrapper/of_integer.hpp>

namespace vk {

	struct queue_family_index : wrapper::of_integer<uint32> {};

	struct src_queue_family_index : queue_family_index {};
	struct dst_queue_family_index : queue_family_index {};

}