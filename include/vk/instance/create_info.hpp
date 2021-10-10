#pragma once

#include "application_info.hpp"
#include "../enabled_extension_name.hpp"
#include "../headers.hpp"

namespace vk {

struct enabled_layer_name : null_terminated_string_view<size_is::undefined> {};

struct instance_create_info {
	unsigned_integer_of_size_of<VkStructureType> type{ (primitive::uint32)VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO };
	const void* next = nullptr;
	uint32 flags;
	vk::application_info* application_info = nullptr;
	uint32 enabled_layer_count;
	const vk::enabled_layer_name* enabled_layer_names = nullptr;
	uint32 enabled_extension_count;
	const vk::enabled_extension_name* enabled_extension_names = nullptr;
};

} // vk

static_assert(sizeof(vk::instance_create_info) == sizeof(VkInstanceCreateInfo));