#pragma once

#include "../../../object/destroy_or_free.hpp"
#include "../../../object/device_child_destroy_base.hpp"
#include "../../device/handle.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::shader_module> : vk::device_child_destroy_base<vk::shader_module, VkShaderModule, vkDestroyShaderModule>{};

} // vk