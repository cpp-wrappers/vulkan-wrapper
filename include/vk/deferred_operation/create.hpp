#pragma once

#include "handle.hpp"

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include "vk/create_or_allocate.hpp"
#include "vk/result.hpp"
#include "vk/device/handle.hpp"
#include "vk/handle/possibly_guarded_handle_of.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::deferred_operation> {

		vk::expected<vk::handle<deferred_operation>>
		operator () (const vk::possibly_guarded_handle_of<vk::device> auto& device) const {
			vk::handle<vk::deferred_operation> deferred_operation;

			vk::result result {
				(int) vkCreateDeferredOperationKHR(
					(VkDevice) vk::get_handle_value(device),
					(VkAllocationCallbacks*) nullptr,
					(VkDeferredOperationKHR*) &deferred_operation
				)
			};
			
			if(result.error()) return result;

			return deferred_operation;
		}

	};

}