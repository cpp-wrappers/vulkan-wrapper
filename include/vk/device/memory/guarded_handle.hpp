#pragma once

#include "free.hpp"
#include "../../shared/guarded_device_child_handle.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::device_memory> : vk::guarded_device_child_handle_base<vk::device_memory> {
		using base_type = vk::guarded_device_child_handle_base<vk::device_memory>;

		using base_type::base_type;
	};

}