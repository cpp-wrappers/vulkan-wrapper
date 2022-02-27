#pragma once

#include "handle.hpp"

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include "vk/device/handle.hpp"
#include "vk/handle/possibly_guarded_handle_of.hpp"
#include "vk/result.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::deferred_operation>
	>::for_types<Args...>
	uint32
	get_max_concurrency(Args&&... args) {
		auto& device =
			elements::vk::possibly_guarded_handle_of<vk::device>(args...);
		auto& deferred_operation =
			elements::vk::possibly_guarded_handle_of<vk::deferred_operation>(args...);

		return vkGetDeferredOperationMaxConcurrencyKHR(
			(VkDevice) vk::get_handle_value(device),
			(VkDeferredOperationKHR) vk::get_handle_value(deferred_operation)
		);
	}

} // vk