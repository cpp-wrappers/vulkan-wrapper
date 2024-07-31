#pragma once

#include "./handle.hpp"
#include "./image_index.hpp"
#include "../__internal/function.hpp"
#include "../__internal/timeout.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__instance/handle.hpp"
#include "../__queue/signal_fence.hpp"
#include "../__queue/signal_semaphore.hpp"
#include "../__device/handle.hpp"
#include "../__semaphore/handle.hpp"
#include "../__fence/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct acquire_next_image_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		handle<vk::swapchain>::underlying_type swapchain,
		uint64 /*vk::timeout*/ timeout,
		handle<vk::semaphore>::underlying_type semaphore,
		handle<vk::fence>::underlying_type fence,
		uint32* image_index
	)> {
		static constexpr auto name = "vkAcquireNextImageKHR";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::swapchain>>.decayed == 1,
		is_same_as<vk::signal_semaphore>.decayed <= 1,
		is_same_as<vk::signal_fence>.decayed <= 1,
		is_same_as<vk::timeout>.decayed <= 1
	>
	[[ nodiscard ]]
	vk::expected<vk::image_index>
	try_acquire_next_image(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::swapchain> swapchain = a.template
			get<is_same_as<handle<vk::swapchain>>.decayed>();
		
		vk::timeout timeout{ ~uint64{ 0 } };

		if constexpr (
			(is_same_as<vk::timeout>.decayed > 0)
			.for_types<Args...>()
		) {
			timeout = a.template
				get<is_same_as<vk::timeout>.decayed>();
		}

		handle<vk::semaphore> semaphore{};

		if constexpr (
			(is_same_as<vk::signal_semaphore>.decayed > 0)
			.for_types<Args...>()
		) {
			semaphore = a.template
				get<is_same_as<vk::signal_semaphore>.decayed>();
		}

		handle<vk::fence> fence{};

		if constexpr (
			(is_same_as<vk::signal_fence>.decayed > 0)
			.for_types<Args...>()
		) {
			fence = a.template get<is_same_as<vk::signal_fence>.decayed>();
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