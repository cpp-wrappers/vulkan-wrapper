#pragma once

#include <core/integer.hpp>

#include "../shared/headers.hpp"
#include "attachment_description.hpp"
#include "subpass_description.hpp"
#include "subpass_dependency.hpp"

namespace vk {

	struct render_pass_create_info {
		uint32 type = (uint32) VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		const void* next{};
		uint32 flags{};
		uint32 attachment_count{};
		const vk::attachment_description* attachments = nullptr;
		uint32 subpass_count{};
		const vk::subpass_description* subpasses = nullptr;
		uint32 dependency_count{};
		const vk::subpass_dependency* dependencies = nullptr;
	};

}

static_assert(sizeof(vk::render_pass_create_info) == sizeof(VkRenderPassCreateInfo));