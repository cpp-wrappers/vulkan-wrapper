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
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<vk::fence_create_flags>.decayed <= 1
	>
	vk::expected<handle<vk::fence>>
	try_create_fence(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		vk::fence_create_info ci {};

		if constexpr (
			(is_same_as<vk::fence_create_flags> > 0).for_types<Args...>()
		) {
			ci.flags = a.template
				get<is_same_as<vk::fence_create_flags>.decayed>();
		}

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
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		(is_same_as<vk::fence_create_flag>.decayed > 0)
	>
	vk::expected<handle<vk::fence>>
	try_create_fence(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		vk::fence_create_flags create_flags;

		a.template for_each([&]<typename Arg>(Arg& arg) {
			if constexpr (same_as<decay<Arg>, vk::fence_create_flag>) {
				create_flags.set(arg);
			}
		});

		return vk::try_create_fence(instance, device, create_flags);
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