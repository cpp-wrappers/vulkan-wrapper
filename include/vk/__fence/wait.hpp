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
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_range_of_decayed<handle<vk::fence>> == 1,
		count_of_decayed_same_as<vk::wait_all> <= 1,
		count_of_decayed_same_as<vk::timeout> <= 1
	>
	vk::result try_wait_for_fences(Args&&... args) {
		tuple a { args... };
		auto& fences = a.template get_range_of_decayed<handle<vk::fence>>();

		bool wait_all = true;

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::wait_all> > 0
		) { wait_all = (bool) a.template get_decayed_same_as<vk::wait_all>(); }

		vk::timeout timeout{ ~uint64{ 0 } };

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::timeout> > 0
		) { timeout = a.template get_decayed_same_as<vk::timeout>(); }

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

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
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::fence>> == 1,
		count_of_decayed_same_as<vk::wait_all> <= 1,
		count_of_decayed_same_as<vk::timeout> <= 1
	>
	vk::result try_wait_for_fence(Args&&... args) {
		handle<vk::fence> fence = tuple{ args... }.template
			get_decayed_same_as<handle<vk::fence>>();

		return tuple{ args... }.template pass_satisfying_predicate<
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