#pragma once

#include "handle.hpp"
#include "destroy.hpp"
#include "bind_memory.hpp"
#include "get_device_address.hpp"
#include "get_memory_requirements.hpp"

#include "vk/handle/guarded/device_child_base.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::buffer> : vk::guarded_device_child_handle_base<vk::buffer> {
		using base_type = vk::guarded_device_child_handle_base<vk::buffer>;

		using base_type::base_type;

		template<typename... Args> vk::result try_bind_memory(Args&&... args) const {
			return vk::try_bind_buffer_memory(device(), handle(), forward<Args>(args)...);
		}

		template<typename... Args> void bind_memory(Args&&... args) const {
			vk::bind_buffer_memory(device(), handle(), forward<Args>(args)...);
		}

		vk::device_address get_device_address() const {
			return vk::get_device_address(device(), handle());
		}

		vk::memory_requirements get_memory_requirements() const {
			return vk::get_memory_requirements(device(), handle());
		}

	};

} // vk