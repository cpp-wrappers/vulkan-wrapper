#pragma once

#include "../handle/guarded/device_child_base.hpp"
#include "destroy.hpp"
#include "handle.hpp"
#include "wait_for_fence.hpp"
#include "reset_fence.hpp"

namespace vk {

	template<>
	struct vk::guarded_handle<vk::fence> : vk::guarded_device_child_handle_base<vk::fence> {
		using base_type = vk::guarded_device_child_handle_base<vk::fence>;

		using base_type::base_type;

		guarded_handle& operator = (guarded_handle&& other) = default;

		template<typename... Args>
		void wait(Args&&... args) const {
			vk::wait_for_fence(device(), handle(), forward<Args>(args)...);
		}

		void reset() const {
			vk::reset_fence(device(), handle());
		}
	};

} // vk