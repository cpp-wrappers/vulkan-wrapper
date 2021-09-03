#pragma once

#include "headers.hpp"
#include <core/integer.hpp>
#include <core/named.hpp>
#include <core/flag_enum.hpp>
#include <core/named.hpp>
#include <cstdint>

namespace vk {

class render_pass;
class image_view;

enum class framebuffer_create_flag {
	imageless = VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT
};

struct attachment_count : named<uint32_t> {};
struct attachments : named<const vk::image_view**> {};

struct framebuffer_create_info {
	uint_with_size_of<VkStructureType> type = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	const void* next{};
	flag_enum<vk::framebuffer_create_flag> flags{};
	vk::render_pass* render_pass{};
	vk::attachment_count attachment_count{};
	vk::attachments attachments{};
	uint32_t width{};
	uint32_t height{};
	uint32_t layers{};
};

} // vk

static_assert(sizeof(vk::framebuffer_create_info) == sizeof(VkFramebufferCreateInfo));