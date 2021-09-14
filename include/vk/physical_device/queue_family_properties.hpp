#pragma once

#include <cstdint>
#include "../headers.hpp"
#include <type_traits>
#include <core/flag_enum.hpp>
#include "../extent.hpp"

namespace vk {

enum class queue_flag : uint32_t {
	graphics = VK_QUEUE_GRAPHICS_BIT,
	compute = VK_QUEUE_COMPUTE_BIT,
	transfer = VK_QUEUE_TRANSFER_BIT,
	sparse_binding = VK_QUEUE_SPARSE_BINDING_BIT,
};

struct queue_family_properties {
	flag_enum<queue_flag> flags;
	uint32_t count;
	uint32_t timestamp_valid_bits;
	vk::extent<3> min_image_transfer_granularity;
};

}

static_assert(sizeof(vk::queue_family_properties) == sizeof(VkQueueFamilyProperties));