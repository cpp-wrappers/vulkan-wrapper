#pragma once

#include "../render_pass/handle.hpp"

#include <core/integer.hpp>
#include <core/flag_enum.hpp>

namespace vk {

	struct render_pass;
	struct image_view;

	enum class framebuffer_create_flag {
		imageless = 0x00000001
	};

	struct framebuffer_create_info {
		uint32 structure_type = 37;
		const void* next;
		flag_enum<vk::framebuffer_create_flag> flags;
		handle<vk::render_pass> render_pass;
		uint32 attachment_count;
		const handle<vk::image_view>* attachments;
		uint32 width;
		uint32 height;
		uint32 layers;
	};

} // vk