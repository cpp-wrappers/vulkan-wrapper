#pragma once

#include "../../../shared/memory_offset.hpp"
#include "../../../shared/offset.hpp"
#include "../../../shared/extent.hpp"
#include "../../image/subresource_layers.hpp"

namespace vk {

	struct buffer_image_copy {
		vk::memory_offset buffer_offset;
		uint32 buffer_row_length;
		uint32 buffer_image_height;
		vk::image_subresource_layers image_subresource;
		vk::offset<3> image_offset;
		vk::extent<3> image_extent;
	};

} // vk

static_assert(sizeof(vk::buffer_image_copy) == sizeof(VkBufferImageCopy));