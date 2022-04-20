#pragma once

#include "query_control.hpp"
#include "query_pipeline_statistic.hpp"

#include "../../subpass.hpp"
#include "../../render_pass/handle.hpp"
#include "../../framebuffer/handle.hpp"

#include <core/integer.hpp>
#include <core/flag_enum.hpp>

namespace vk {

	struct occlusion_query_enable { uint32 _; };

	struct command_buffer_inheritance_info {
		uint32 structure_type = 41;
		const void* next;
		handle<vk::render_pass> render_pass;
		vk::subpass subpass;
		handle<vk::framebuffer> framebuffer;
		vk::occlusion_query_enable occlusion_query_enable;
		vk::query_control_flags query_flags;
		vk::query_pipeline_statistic_flags pipeline_statistics_flags;
	};

} // vk