#pragma once

#include "handle.hpp"

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include <core/handle/possibly_guarded_of.hpp>
#include "vk/device/handle.hpp"
#include "vk/result.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_one_possibly_guarded_handle_of<vk::deferred_operation>
	>::for_types<Args...>
	vk::result
	get_result(Args&&... args) {
		auto& device =
			elements::possibly_guarded_handle_of<vk::device>(args...);
		auto& deferred_operation =
			elements::possibly_guarded_handle_of<vk::deferred_operation>(args...);

		return (int) vkGetDeferredOperationResultKHR(
			(VkDevice) vk::get_handle_value(device),
			(VkDeferredOperationKHR) vk::get_handle_value(deferred_operation)
		);
	}

} // vk