#pragma once

#include "query_control.hpp"
#include "query_pipeline_statistic.hpp"

#include "../__internal/subpass.hpp"
#include "../__framebuffer/handle.hpp"
#include "../__render_pass/handle.hpp"

namespace vk {

	struct occlusion_query_enable { uint32 _; };

	struct command_buffer_inheritance_info {
		uint32 structure_type = 41;
		const void* next;
		handle<vk::render_pass>::underlying_type render_pass;
		vk::subpass subpass;
		handle<vk::framebuffer>::underlying_type framebuffer;
		vk::occlusion_query_enable occlusion_query_enable;
		vk::query_control_flags query_flags;
		vk::query_pipeline_statistic_flags pipeline_statistics_flags;
	};

} // vk