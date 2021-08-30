#pragma once

#include "headers.hpp"
#include <core/integer.hpp>
#include <core/null_terminated_string_view.hpp>
#include "application_info.hpp"

namespace vk {

struct enabled_layer_name : null_terminated_string_view<size_is::undefined> {};
struct enabled_extension_name : null_terminated_string_view<size_is::undefined> {};

struct instance_create_info {
	int_with_size_of<VkStructureType> type = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	const void* next = nullptr;
	uint32_t flags = 0;
	vk::application_info* application_info = nullptr;
	uint32_t enabled_layer_count = 0;
	const vk::enabled_layer_name* enabled_layer_names = nullptr;
	uint32_t enabled_extension_count = 0;
	const vk::enabled_extension_name* enabled_extension_names = nullptr;
};

} // vk

static_assert(sizeof(vk::instance_create_info) == sizeof(VkInstanceCreateInfo));