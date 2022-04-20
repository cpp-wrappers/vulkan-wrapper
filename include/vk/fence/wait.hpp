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
	vk::timeout timeout
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_contain_range_of<handle<vk::fence>>,
		types::are_may_contain_one_decayed<vk::wait_all>,
		types::are_may_contain_one_decayed<vk::timeout>
	>::for_types<Args...>
	vk::result try_wait_for_fences(Args&&... args) {
		auto& fences = elements::range_of<handle<vk::fence>>(args...);

		bool wait_all = true;

		if constexpr (
			types::are_contain_decayed<vk::wait_all>::for_types<Args...>
		) { wait_all = (bool) elements::decayed<vk::wait_all>(args...); }

		vk::timeout timeout{ ~uint64{ 0 } };

		if constexpr (
			types::are_contain_decayed<vk::timeout>::for_types<Args...>
		) { timeout = elements::decayed<vk::timeout>(args...); }

		auto device = elements::decayed<handle<vk::device>>(args...);

		return {
			vkWaitForFences(
				device,
				(uint32) fences.size(),
				fences.data(),
				uint32{ wait_all },
				timeout
			)
		};
	} // try_wait_for_fences

	template<typename... Args>
	void wait_for_fences(Args&&... args) {
		vk::result result = vk::try_wait_for_fences(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_contain_one_decayed<handle<vk::fence>>,
		types::are_may_contain_one_decayed<vk::wait_all>,
		types::are_may_contain_one_decayed<vk::timeout>
	>::for_types<Args...>
	vk::result try_wait_for_fence(Args&&... args) {
		auto fence = elements::decayed<handle<vk::fence>>(args...);

		return elements::pass_not_satisfying_type_predicate<
			type::is_decayed<handle<vk::fence>>
		>(
			array{ handle<vk::fence>{ fence } },
			forward<Args>(args)...
		)(
			[&]<typename... Others>(Others&&... others) {
				return vk::try_wait_for_fences(
					forward<Others>(others)...
				);
			}
		);
	} // try_wait_for_fence

	template<typename... Args>
	void wait_for_fence(Args&&... args) {
		vk::result result = vk::try_wait_for_fence(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk

template<typename... Args>
void
handle<vk::device>::wait_for_fence(Args&&... args) const {
	vk::wait_for_fence(*this, forward<Args>(args)...);
}