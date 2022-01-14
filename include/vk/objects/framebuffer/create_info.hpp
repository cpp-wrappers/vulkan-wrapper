#pragma once

#include <core/integer.hpp>
#include <core/flag_enum.hpp>
#include <core/wrapper/of_pointer_to.hpp>
#include <core/wrapper/of_integer.hpp>

#include "../../shared/headers.hpp"
#include "../render_pass/handle.hpp"

namespace vk {

	struct render_pass;
	struct image_view;

	enum class framebuffer_create_flag {
		imageless = VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT
	};

	struct framebuffer_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		const void* const next;
		flag_enum<vk::framebuffer_create_flag> flags;
		vk::handle<vk::render_pass> render_pass;
		uint32 attachment_count;
		const vk::handle<vk::image_view>* attachments;
		uint32 width;
		uint32 height;
		uint32 layers;
	};

} // vk

static_assert(sizeof(vk::framebuffer_create_info) == sizeof(VkFramebufferCreateInfo));