#pragma once

#include "handle.hpp"

#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include "vk/device/handle.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_one_range_of<vk::handle<vk::fence>>,
		types::are_may_contain_one_decayed<vk::wait_all>,
		types::are_may_contain_one_decayed<vk::timeout>
	>::for_types<Args...>
	vk::result try_wait_for_fences(Args&&... args) {
		auto& fences = elements::range_of<vk::handle<vk::fence>>(args...);

		bool wait_all = true;

		if constexpr(types::are_contain_decayed<vk::wait_all>::for_types<Args...>) {
			wait_all = (bool) elements::decayed<vk::wait_all>(args...);
		}

		vk::timeout timeout{ UINT64_MAX };

		if constexpr(types::are_contain_decayed<vk::timeout>::for_types<Args...>) {
			timeout = elements::decayed<vk::timeout>(args...);
		}

		auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);

		return {
			(int32) vkWaitForFences(
				(VkDevice) vk::get_handle_value(device),
				(uint32) fences.size(),
				(VkFence*) fences.data(),
				uint32{ wait_all },
				(uint64) timeout
			)
		};
	}

	template<typename... Args>
	void wait_for_fences(Args&&... args) {
		vk::result result = vk::try_wait_for_fences(forward<Args>(args)...);
		if(result.error()) vk::default_unexpected_handler(result);
	}

} // vk