#pragma once

#include "./handle.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"

#include <tuple.hpp>
#include <types.hpp>

namespace vk {

	struct reset_fences_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		uint32 fence_count,
		const handle<vk::fence>::underlying_type* fences
	)> {
		static constexpr auto name = "vkResetFences";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_range_of<is_same_as<handle<vk::fence>>.decayed> == 1
	>
	vk::result try_reset_fences(Args&&... args) {
		tuple a { args... };
		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();
		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();
		auto& fences = a.template
			get<is_range_of<is_same_as<handle<vk::fence>>.decayed>>();
		return {
			vk::get_device_function<vk::reset_fences_function>(
				instance, device
			)(
				device.underlying(),
				(uint32) fences.size(),
				(const handle<vk::fence>::underlying_type*) fences.iterator()
			)
		};
	}

	template<typename... Args>
	void reset_fences(Args&&... args) {
		vk::result result = vk::try_reset_fences(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::fence>>.decayed == 1
	>
	vk::result try_reset_fence(Args&&... args) {
		tuple a { args... };
		return vk::try_reset_fences(
			a.template get<is_same_as<handle<vk::instance>>.decayed>(),
			a.template get<is_same_as<handle<vk::device>>.decayed>(),
			array { a.template get<is_same_as<handle<vk::fence>>.decayed>() }
		);
	}

	template<typename... Args>
	void reset_fence(Args&&... args) {
		auto result = vk::try_reset_fence(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk