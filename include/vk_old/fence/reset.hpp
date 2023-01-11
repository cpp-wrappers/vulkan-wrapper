#pragma once

#include "handle.hpp"

#include "../function.hpp"
#include "../device/handle.hpp"

extern "C" VK_ATTR int32 VK_CALL vkResetFences(
	handle<vk::device>       device,
	uint32                   fence_count,
	const handle<vk::fence>* fences
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_contain_range_of<handle<vk::fence>>
	>::for_types<Args...>
	vk::result try_reset_fences(Args&&... args) {
		auto& fences = elements::range_of<handle<vk::fence>>(args...);
		auto device = elements::decayed<handle<vk::device>>(args...);
		return {
			vkResetFences(
				device,
				(uint32) fences.size(),
				fences.data()
			)
		};
	}

	template<typename... Args>
	void reset_fences(Args&&... args) {
		auto result = vk::try_reset_fences(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_contain_one_decayed<handle<vk::fence>>
	>::for_types<Args...>
	vk::result try_reset_fence(Args&&... args) {
		return vk::try_reset_fences(
			array{ elements::decayed<handle<vk::fence>>(args...) },
			elements::decayed<handle<vk::device>>(args...)
		);
	}

	template<typename... Args>
	void reset_fence(Args&&... args) {
		auto result = vk::try_reset_fence(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk

void inline
handle<vk::device>::reset_fence(handle<vk::fence> fence) const {
	vk::reset_fence(*this, fence);
}