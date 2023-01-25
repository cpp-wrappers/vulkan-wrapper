#pragma once

#include "handle.hpp"

#include "../device/handle.hpp"
#include "../result.hpp"
#include "../function.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

typedef uint32 (VK_PTR *PFN_vkGetDeferredOperationMaxConcurrencyKHR)(
	handle<vk::device> device,
	handle<vk::deferred_operation> operation
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_contain_one_decayed<handle<vk::deferred_operation>>
	>::for_types<Args...>
	uint32
	get_max_concurrency(Args&&... args) {
		auto device = elements::decayed<handle<vk::device>>(args...);
		auto deferred_operation {
			elements::decayed<handle<vk::deferred_operation>>(args...)
		};

		auto f = (PFN_vkGetDeferredOperationMaxConcurrencyKHR)
			vk::get_device_proc_address(
				device, "vkGetDeferredOperationMaxConcurrencyKHR"
			);

		return f(device, deferred_operation);
	}

} // vk