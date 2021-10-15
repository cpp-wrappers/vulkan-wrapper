#pragma once

#include "../headers.hpp"

#include <core/integer.hpp>
#include <core/flag_enum.hpp>
#include <core/pointer.hpp>

namespace vk {

struct render_pass;
struct image_view;

enum class framebuffer_create_flag {
	imageless = VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT
};

struct attachment_count : uint32 {};
struct attachments : pointer_of<const vk::image_view*> {};

struct framebuffer_create_info {
	uint32 type = (primitive::uint32) VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	const void* next{};
	flag_enum<vk::framebuffer_create_flag> flags{};
	vk::render_pass* render_pass{};
	vk::attachment_count attachment_count{};
	vk::attachments attachments{};
	uint32 width{};
	uint32 height{};
	uint32 layers{};
};

} // vk

static_assert(sizeof(vk::framebuffer_create_info) == sizeof(VkFramebufferCreateInfo));