#pragma once

#include "../__internal/memory_offset.hpp"
#include "../__internal/offset.hpp"
#include "../__internal/extent.hpp"
#include "../__image/subresource_layers.hpp"

namespace vk {

	struct buffer_image_copy {
		uint64 /*vk::memory_offset*/ buffer_offset = 0;
		uint32 buffer_row_length;
		uint32 buffer_image_height;
		vk::image_subresource_layers image_subresource;
		vk::offset<3> image_offset{};
		vk::extent<3> image_extent;
	};

} // vk