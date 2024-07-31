#pragma once

#include "../__internal/function.hpp"
#include "../__internal/timeout.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"
#include "../__fence/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct wait_for_fences_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		uint32 fence_count,
		const handle<vk::fence>::underlying_type* fences,
		uint32 wait_all,
		uint64 /*vk::timeout*/ timeout
	)> {
		static constexpr auto name = "vkWaitForFences";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_range_of<is_same_as<handle<vk::fence>>.decayed> == 1,
		is_same_as<vk::wait_all>.decayed <= 1,
		is_same_as<vk::timeout>.decayed <= 1
	>
	vk::result try_wait_for_fences(Args&&... args) {
		tuple a { args... };
		auto& fences = a.template
			get<is_range_of<is_same_as<handle<vk::fence>>.decayed>>();

		bool wait_all = true;

		if constexpr (
			(is_same_as<vk::wait_all>.decayed > 0).for_types<Args...>()
		) { wait_all = (bool) a.template get<is_same_as<vk::wait_all>.decayed>(); }

		vk::timeout timeout{ ~uint64{ 0 } };

		if constexpr (
			(is_same_as<vk::timeout>.decayed > 0).for_types<Args...>()
		) { timeout = a.template get<is_same_as<vk::timeout>.decayed>(); }

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		return {
			vk::get_device_function<vk::wait_for_fences_function>(
				instance, device
			)(
				device.underlying(),
				(uint32) fences.size(),
				(const handle<vk::fence>::underlying_type*) fences.iterator(),
				uint32{ wait_all },
				timeout
			)
		};
	} // try_wait_for_fences

	template<typename... Args>
	void wait_for_fences(Args&&... args) {
		vk::result result = vk::try_wait_for_fences(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::fence>>.decayed == 1,
		is_same_as<vk::wait_all>.decayed <= 1,
		is_same_as<vk::timeout>.decayed <= 1
	>
	vk::result try_wait_for_fence(Args&&... args) {
		handle<vk::fence> fence = tuple{ args... }.template
			get<is_same_as<handle<vk::fence>>.decayed>();

		return tuple{ args... }.template pass<
			!is_same_as<handle<vk::fence>>.decayed
		>([&]<typename... Args0>(Args0&&... args0) {
			return vk::try_wait_for_fences(
				forward<Args0>(args0)..., array{ fence }
			);
		});
	} // try_wait_for_fence

	template<typename... Args>
	void wait_for_fence(Args&&... args) {
		vk::result result = vk::try_wait_for_fence(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk