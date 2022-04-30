#pragma once

#include "handle.hpp"

#include "../function.hpp"
#include "../destroy_or_free.hpp"
#include "../device_child_destroy_base.hpp"
#include "../device/handle.hpp"

extern "C" VK_ATTR void VK_CALL vkDestroyPipeline(
	handle<vk::device>   device,
	handle<vk::pipeline> pipeline,
	const void*          allocator
);

namespace vk {

	template<>
	struct vk::destroy_t<vk::pipeline> :
		vk::device_child_destroy_base<vk::pipeline, vkDestroyPipeline>
	{};

} // vk