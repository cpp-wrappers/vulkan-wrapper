#pragma once

#include <core/integer.hpp>
#include <core/flag_enum.hpp>
#include "../../shared/headers.hpp"
#include "../../render_pass/handle.hpp"
#include "../../framebuffer/handle.hpp"
#include "query_control.hpp"
#include "query_pipeline_statistics.hpp"
#include "../../shared/subpass.hpp"

namespace vk {

	struct occlusion_query_enable : wrapper::of_integer<uint32> {};

	struct command_buffer_inheritance_info {
		const uint32 type = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
		const void* next = nullptr;
		vk::render_pass render_pass;
		vk::subpass subpass;
		vk::framebuffer framebuffer;
		vk::occlusion_query_enable occlusion_query_enable;
		flag_enum<vk::query_control> query_flags;
		flag_enum<vk::query_pipeline_statistics> pipeline_statistics;
	};
}

static_assert(sizeof(vk::command_buffer_inheritance_info) == sizeof(VkCommandBufferInheritanceInfo));