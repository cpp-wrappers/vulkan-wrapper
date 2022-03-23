#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include <core/meta/elements/one_of.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

#include "vk/create_or_allocate.hpp"
#include "vk/device/handle.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::fence> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_may_contain_one_decayed<vk::fence_create_flags>
		>::for_types<Args...>
		vk::expected<handle<vk::fence>>
		operator () (Args&&... args) const {
			vk::fence_create_info ci {};
	
			if constexpr(types::are_contain_decayed<vk::fence_create_flags>::for_types<Args...>) {
				ci.flags = elements::decayed<vk::fence_create_flags>(args...);
			}
	
			auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);
			VkFence fence;
	
			vk::result result {
				(int32) vkCreateFence(
					(VkDevice) vk::get_handle_value(device),
					(VkFenceCreateInfo*) &ci,
					(VkAllocationCallbacks*) nullptr,
					(VkFence*) &fence
				)
			};
	
			if(result.success()) return handle<vk::fence>{ fence };
	
			return result;
		}

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_may_contain_decayed<vk::fence_create_flag>
		>::for_types<Args...>
		vk::expected<handle<vk::fence>>
		operator () (Args&&... args) const {
			auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);

			vk::fence_create_flags create_flags;

			elements::for_each_decayed<vk::fence_create_flag>(args...)(
				[&](vk::fence_create_flag flag){ create_flags.set(flag); }
			);

			return this-> operator() (device, create_flags);
		}

	};

} // vk