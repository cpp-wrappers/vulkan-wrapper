#pragma once

#include "../__render_pass/handle.hpp"
#include "../__image_view/handle.hpp"

#include <enum_flags.hpp>

namespace vk {

	struct render_pass;
	struct image_view;

	enum class framebuffer_create_flag {
		imageless = 0x00000001
	};

	struct framebuffer_create_info {
		uint32 structure_type = 37;
		const void* next = nullptr;
		enum_flags<vk::framebuffer_create_flag> flags{};
		handle<vk::render_pass>::underlying_type render_pass;
		uint32 attachment_count;
		const handle<vk::image_view>::underlying_type* attachments;
		uint32 width;
		uint32 height;
		uint32 layers;
	};

} // vk