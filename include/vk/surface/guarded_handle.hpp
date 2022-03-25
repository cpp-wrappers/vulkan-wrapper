#pragma once

#include "handle.hpp"
#include "destroy.hpp"

#include <core/exchange.hpp>

#include "vk/handle/guarded/instance_child_base.hpp"

namespace vk {

	struct instance;

} // vk

template<>
struct guarded_handle<vk::surface> :
	vk::guarded_instance_child_handle_base<vk::surface>
{
	using base_type = vk::guarded_instance_child_handle_base<vk::surface>;
	using base_type::base_type;
};