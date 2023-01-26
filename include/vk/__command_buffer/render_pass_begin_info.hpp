#pragma once

#include "./clear.hpp"
#include "../__internal/rect2d.hpp"
#include "../__render_pass/handle.hpp"
#include "../__framebuffer/handle.hpp"

namespace vk {

	struct render_area : vk::rect2d {

		render_area(vk::offset<2> offset, vk::extent<2> extent) :
			vk::rect2d{ offset, extent }
		{}

		render_area(vk::extent<2> extent) :
			vk::rect2d{ vk::offset<2>{ 0,0 }, extent }
		{}
	};

	struct render_pass_begin_info {
		uint32 structure_type = 43;
		const void* next = nullptr;
		handle<vk::render_pass>::underlying_type render_pass;
		handle<vk::framebuffer>::underlying_type framebuffer;
		vk::render_area render_area;
		uint32 clear_value_count = 0;
		const vk::clear_value* clear_values = nullptr;
	};

} // vk