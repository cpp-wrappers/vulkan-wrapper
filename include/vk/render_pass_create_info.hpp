#pragma once

#include "headers.hpp"
#include <core/integer.hpp>
#include <vulkan/vulkan_core.h>
#include "attachment_description.hpp"
#include "subpass_description.hpp"
#include "subpass_dependency.hpp"

namespace vk {

struct render_pass_create_info {
	uint_with_size_of<VkStructureType> type = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	const void* next = nullptr;
	uint_with_size_of<VkRenderPassCreateFlags> flags = 0;
	uint32_t attachment_count = 0;
	const vk::attachment_description* attachments = nullptr;
	uint32_t subpass_count = 0;
	const vk::subpass_description* subpasses = nullptr;
	uint32_t dependency_count = 0;
	const vk::subpass_dependency* dependencies = nullptr;
};

}

static_assert(sizeof(vk::render_pass_create_info) == sizeof(VkRenderPassCreateInfo));