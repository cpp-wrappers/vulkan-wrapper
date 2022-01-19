#pragma once

#include "../../object/destroy_or_free.hpp"
#include "../../object/device_child_destroy_base.hpp"
#include "../device/handle.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::render_pass> : vk::device_child_destroy_base<vk::render_pass, VkRenderPass, vkDestroyRenderPass> {};

} // vk