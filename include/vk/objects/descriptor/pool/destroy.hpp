#pragma once

#include "../../../object/destroy_or_free.hpp"
#include "../../../object/device_child_destroy_base.hpp"
#include "../../device/handle.hpp"
#include "handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::descriptor_pool> : vk::device_child_destroy_base<vk::descriptor_pool, VkDescriptorPool, vkDestroyDescriptorPool>{};

} // vk