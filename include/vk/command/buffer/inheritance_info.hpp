#pragma once

#include <core/integer.hpp>
#include <core/flag_enum.hpp>

#include "../../shared/headers.hpp"
#include "../../render_pass/handle.hpp"
#include "../../framebuffer/handle.hpp"
#include "../../shared/subpass.hpp"
#include "query_control.hpp"
#include "query_pipeline_statistic.hpp"

namespace vk {

	struct occlusion_query_enable : wrapper::of_integer<uint32> {};

	struct command_buffer_inheritance_info {
		const uint32 type = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
		const void* next;
		vk::handle<vk::render_pass> render_pass;
		vk::subpass subpass;
		vk::handle<vk::framebuffer> framebuffer;
		vk::occlusion_query_enable occlusion_query_enable;
		vk::query_control_flags query_flags;
		vk::query_pipeline_statistic_flags pipeline_statistics_flags;
	};
}

static_assert(sizeof(vk::command_buffer_inheritance_info) == sizeof(VkCommandBufferInheritanceInfo));