#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include "../create_or_allocate.hpp"
#include "../device/handle.hpp"
#include "../function.hpp"

#include <core/meta/elements/one_of.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR int32 VK_CALL vkCreateFence(
	handle<vk::device> device,
	const vk::fence_create_info* create_info,
	const void* allocator,
	handle<vk::fence>* fence
);

namespace vk {

	template<>
	struct vk::create_t<vk::fence> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<handle<vk::device>>,
			types::are_may_contain_one_decayed<vk::fence_create_flags>
		>::for_types<Args...>
		vk::expected<handle<vk::fence>>
		operator () (Args&&... args) const {
			vk::fence_create_info ci {};
	
			if constexpr (
				types::are_contain_decayed<
					vk::fence_create_flags
				>::for_types<Args...>
			) { ci.flags = elements::decayed<vk::fence_create_flags>(args...); }
	
			auto device = elements::decayed<handle<vk::device>>(args...);
			handle<vk::fence> fence;
	
			vk::result result {
				vkCreateFence(
					device,
					&ci,
					nullptr,
					&fence
				)
			};
	
			if(result.success()) return handle<vk::fence>{ fence };
	
			return result;
		}

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<handle<vk::device>>,
			types::are_may_contain_decayed<vk::fence_create_flag>
		>::for_types<Args...>
		vk::expected<handle<vk::fence>>
		operator () (Args&&... args) const {
			auto device = elements::decayed<handle<vk::device>>(args...);

			vk::fence_create_flags create_flags;

			elements::for_each_decayed<vk::fence_create_flag>(args...)(
				[&](vk::fence_create_flag flag){ create_flags.set(flag); }
			);

			return this-> operator() (device, create_flags);
		}

	}; // create_t<fence>

} // vk