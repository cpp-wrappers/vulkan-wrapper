#pragma once

#include "handle.hpp"
#include "destroy.hpp"
#include "get_device_address.hpp"

#include "vk/handle/guarded/device_child_base.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::acceleration_structure> :
		vk::guarded_device_child_handle_base<vk::acceleration_structure>
	{
		using base_type = vk::guarded_device_child_handle_base<vk::acceleration_structure>;
		using base_type::base_type;

		vk::device_address get_device_address() const {
			return vk::get_device_address(device(), handle());
		}
	};

} // vk