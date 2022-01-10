#pragma once

#include "../../../object/handle/guarded/device_child_base.hpp"
#include "destroy.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::descriptor_pool> : vk::guarded_device_child_handle_base<vk::descriptor_pool> {
		using base_type = vk::guarded_device_child_handle_base<vk::descriptor_pool>;

		using base_type::base_type;
	};

} // vk