#pragma once

#include "../result.hpp"
#include "../handle/base.hpp"

namespace vk {

	struct queue;

} // vk

template<>
struct handle<vk::queue> : vk::handle_base<vk::dispatchable> {

	template<typename... Args>
	void submit(Args&&... args) const;

	template<typename... Args> vk::result try_present(Args&&...) const;
	template<typename... Args> void present(Args&&...) const;
};

#include "submit.hpp"

template<typename... Args>
void handle<vk::queue>::submit(Args&&... args) const {
	vk::queue_submit(*this, forward<Args>(args)...);
}

#include "present.hpp"

template<typename... Args>
vk::result handle<vk::queue>::try_present(Args&&... args) const {
	return vk::try_queue_present(*this, forward<Args>(args)...);
}

template<typename... Args>
void handle<vk::queue>::present(Args&&... args) const {
	vk::queue_present(*this, forward<Args>(args)...);
}