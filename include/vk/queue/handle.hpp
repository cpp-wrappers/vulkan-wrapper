#pragma once

#include "../shared/result.hpp"
#include "../shared/handle.hpp"

namespace vk {

	struct queue;

	template<>
	struct vk::handle<vk::queue> : vk::handle_base<vk::dispatchable> {

		template<typename... Args>
		void submit(Args&&... args) const;

		template<typename... Args> vk::result try_present(Args&&...) const;
		template<typename... Args> void present(Args&&...) const;
	};
}

#include "submit.hpp"

template<typename... Args>
void vk::handle<vk::queue>::submit(Args&&... args) const {
	vk::queue_submit(*this, forward<Args>(args)...);
}

#include "present.hpp"

template<typename... Args>
vk::result vk::handle<vk::queue>::try_present(Args&&... args) const {
	return vk::try_queue_present(*this, forward<Args>(args)...);
}

template<typename... Args>
void vk::handle<vk::queue>::present(Args&&... args) const {
	vk::queue_present(*this, forward<Args>(args)...);
}