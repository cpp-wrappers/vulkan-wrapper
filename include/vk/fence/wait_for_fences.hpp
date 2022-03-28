#pragma once

#include "handle.hpp"

#include "../device/handle.hpp"
#include "../function.hpp"

#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR int32 VK_CALL vkWaitForFences(
	handle<vk::device> device,
	uint32 fence_count,
	const handle<vk::fence>* fences,
	uint32 wait_all,
	uint64 timeout
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_range_of<handle<vk::fence>>,
		types::are_may_contain_one_decayed<vk::wait_all>,
		types::are_may_contain_one_decayed<vk::timeout>
	>::for_types<Args...>
	vk::result try_wait_for_fences(Args&&... args) {
		auto& fences = elements::range_of<handle<vk::fence>>(args...);

		bool wait_all = true;

		if constexpr(
			types::are_contain_decayed<vk::wait_all>::for_types<Args...>
		) { wait_all = (bool) elements::decayed<vk::wait_all>(args...); }

		vk::timeout timeout{ ~uint64{ 0 } };

		if constexpr(
			types::are_contain_decayed<vk::timeout>::for_types<Args...>
		) { timeout = elements::decayed<vk::timeout>(args...); }

		auto& device = elements::possibly_guarded_handle_of<
			vk::device
		>(args...);

		return {
			vkWaitForFences(
				vk::get_handle(device),
				(uint32) fences.size(),
				fences.data(),
				uint32{ wait_all },
				(uint64) timeout
			)
		};
	}

	template<typename... Args>
	void wait_for_fences(Args&&... args) {
		vk::result result = vk::try_wait_for_fences(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk