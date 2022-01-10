#pragma once

#include <core/exchange.hpp>

#include "../../object/handle/guarded/instance_child_base.hpp"
#include "handle.hpp"
#include "destroy.hpp"

namespace vk {
	struct instance;

	template<>
	struct vk::guarded_handle<vk::surface> : vk::guarded_instance_child_handle_base<vk::surface> {
		using base_type = vk::guarded_instance_child_handle_base<vk::surface>;

		using base_type::base_type;

		guarded_handle& operator = (guarded_handle&&) = default;
	};
}