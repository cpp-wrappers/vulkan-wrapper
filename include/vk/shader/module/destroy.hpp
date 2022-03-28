#pragma once

#include "handle.hpp"

#include "../../destroy_or_free.hpp"
#include "../../device_child_destroy_base.hpp"
#include "../../device/handle.hpp"
#include "../../function.hpp"

extern "C" VK_ATTR void VK_CALL vkDestroyShaderModule(
	handle<vk::device> device,
	handle<vk::shader_module> shader_module,
	const void* allocator
);

namespace vk {

	template<>
	struct vk::destroy_t<vk::shader_module> :
		vk::device_child_destroy_base<vk::shader_module, vkDestroyShaderModule>
	{};

} // vk