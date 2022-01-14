#pragma once

#include <core/integer.hpp>

#include "../../../shared/headers.hpp"
#include "../../../shared/rect2d.hpp"
#include "../../render_pass/handle.hpp"
#include "../../framebuffer/handle.hpp"
#include "clear.hpp"

namespace vk {

	struct render_area : wrapper::of<vk::rect2d> {

		render_area(vk::offset<2> offset, vk::extent<2> extent)
			: wrapper::of<vk::rect2d>{ offset, extent }
		{}

		render_area(vk::extent<2> extent)
			: wrapper::of<vk::rect2d>{ vk::offset<2>{ 0,0 }, extent }
		{}
	};

	struct render_pass_begin_info {
		const uint32 type = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		const void* const next;
		vk::handle<vk::render_pass> render_pass;
		vk::handle<vk::framebuffer> framebuffer;
		vk::render_area render_area;
		uint32 clear_value_count;
		vk::clear_value* clear_values;
	};

} // vk

static_assert(sizeof(vk::render_pass_begin_info) == sizeof(VkRenderPassBeginInfo));