#pragma once

#include "handle.hpp"

#include "../create_or_allocate.hpp"
#include "../result.hpp"
#include "../function.hpp"
#include "../device/handle.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/handle/possibly_guarded_of.hpp>

extern "C" VK_ATTR int32 VK_CALL vkCreateDeferredOperationKHR(
	handle<vk::device> device,
	const void* allocator,
	handle<vk::deferred_operation>* deferred_operation
);

namespace vk {

	template<>
	struct vk::create_t<vk::deferred_operation> {

		template<possibly_guarded_handle_of<vk::device> Device>
		vk::expected<handle<deferred_operation>>
		operator () (Device&& device) const {
			handle<vk::deferred_operation> deferred_operation;

			vk::result result {
				(int) vkCreateDeferredOperationKHR(
					vk::get_handle(device),
					nullptr,
					&deferred_operation
				)
			};
			
			if(result.error()) return result;

			return deferred_operation;

		} // operator ()

	}; // create_t<deferred_operation>

} // vk