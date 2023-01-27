#pragma once

#include "./handle.hpp"
#include "./image_index.hpp"
#include "../__internal/function.hpp"
#include "../__internal/timeout.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"
#include "../__semaphore/handle.hpp"
#include "../__fence/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct acquire_next_image_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::swapchain>::underlying_type swapchain,
		vk::timeout timeout,
		handle<vk::semaphore>::underlying_type semaphore,
		handle<vk::fence>::underlying_type fence,
		uint32* image_index
	)> {
		static constexpr auto name = "vkAcquireNextImageKHR";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::swapchain>> == 1,
		count_of_decayed_same_as<handle<vk::semaphore>> <= 1,
		count_of_decayed_same_as<handle<vk::fence>> <= 1,
		count_of_decayed_same_as<vk::timeout> <= 1
	>
	[[ nodiscard ]]
	vk::expected<vk::image_index>
	try_acquire_next_image(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::swapchain> swapchain = a.template
			get_decayed_same_as<handle<vk::swapchain>>();
		
		vk::timeout timeout{ ~uint64{ 0 } };

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::timeout> > 0
		) {
			timeout = a.template
				get_decayed_same_as<vk::timeout>();
		}

		handle<vk::semaphore> semaphore{};

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<handle<vk::semaphore>> > 0
		) {
			semaphore = a.template
				get_decayed_same_as<handle<vk::semaphore>>();
		}

		handle<vk::fence> fence{};

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<handle<vk::fence>> > 0
		) {
			fence = a.template get_decayed_same_as<handle<vk::fence>>();
		}

		uint32 index;

		vk::result result {
			vk::get_device_function<vk::acquire_next_image_function>(
				instance, device
			)(
				device.underlying(),
				swapchain.underlying(),
				timeout,
				semaphore.underlying(),
				fence.underlying(),
				&index
			)
		};

		if(result.error()) return result;

		return vk::image_index{ index };
	}

} // vk