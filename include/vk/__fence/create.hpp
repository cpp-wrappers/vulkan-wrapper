#pragma once

#include "./handle.hpp"
#include "./create_info.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"

#include <tuple.hpp>
#include <types.hpp>

namespace vk {

	struct create_fence_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		const vk::fence_create_info* create_info,
		const void* allocator,
		handle<vk::fence>::underlying_type* fence
	)> {
		static constexpr auto name = "vkCreateFence";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_convertible_to<handle<vk::instance>> == 1,
		is_convertible_to<handle<vk::device>> == 1,
		(
			is_same_as<vk::fence_create_flags>.decayed <= 1 ||
			is_same_as<vk::fence_create_flag>.decayed > 0
		)
	>
	vk::expected<handle<vk::fence>>
	try_create_fence(Args&&... args) {
		tuple a { args... };

		auto instance = (handle<vk::instance>) a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		auto device = (handle<vk::device>) a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		vk::fence_create_info ci {};

		if constexpr (
			(is_same_as<vk::fence_create_flags> > 0).for_types<Args...>()
		) {
			ci.flags = a.template
				get<is_same_as<vk::fence_create_flags>.decayed>();
		}
		a.template pass<is_same_as<vk::fence_create_flag>.decayed>(
			[&](auto... flags){ (ci.flags.set(flags), ...); }
		);

		handle<vk::fence> fence;

		vk::result result {
			vk::get_device_function<vk::create_fence_function>(
				instance, device
			)(
				device.underlying(),
				&ci,
				nullptr,
				&fence.underlying()
			)
		};

		if (result.success()) return handle<vk::fence>{ fence };

		return result;
	}

	template<typename... Args>
	handle<vk::fence> create_fence(Args&&... args) {
		vk::expected<handle<vk::fence>> result
			= vk::try_create_fence(forward<Args>(args)...);
		if (result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk