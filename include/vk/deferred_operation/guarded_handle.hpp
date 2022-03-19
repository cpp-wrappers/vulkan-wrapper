#pragma once

#include "handle.hpp"

#include "vk/handle/guarded/device_child_base.hpp"

namespace vk {

	template<>
	struct guarded_handle<vk::deferred_operation> :
		vk::guarded_device_child_handle_base<vk::deferred_operation>
	{
		using base_type = vk::guarded_device_child_handle_base<vk::deferred_operation>;
		using base_type::base_type;
	};

}

#include "destroy.hpp"