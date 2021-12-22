#pragma once

#include <core/integer.hpp>

#include "../../shared/headers.hpp"
#include "../../render_pass/handle.hpp"
#include "../../framebuffer/handle.hpp"
#include "../../shared/rect2d.hpp"
#include "clear.hpp"

namespace vk {

	struct render_pass_begin_info {
		const uint32 type = (uint32) VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		const void* next;
		vk::handle<vk::render_pass> render_pass;
		vk::handle<vk::framebuffer> framebuffer;
		vk::rect2d render_area;
		uint32 clear_value_count;
		vk::clear_value* clear_values;
	};
}

static_assert(sizeof(vk::render_pass_begin_info) == sizeof(VkRenderPassBeginInfo));