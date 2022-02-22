#pragma once

#include "attachment_description.hpp"
#include "subpass_description.hpp"
#include "subpass_dependency.hpp"

#include <core/integer.hpp>

#include "vk/headers.hpp"

namespace vk {

	struct render_pass_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		const void* const next;
		uint32 flags;
		uint32 attachment_count;
		const vk::attachment_description* attachments;
		uint32 subpass_count;
		const vk::subpass_description* subpasses;
		uint32 dependency_count;
		const vk::subpass_dependency* dependencies;
	};
}

static_assert(sizeof(vk::render_pass_create_info) == sizeof(VkRenderPassCreateInfo));