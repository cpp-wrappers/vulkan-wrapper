#pragma once

#include "./handle.hpp"
#include "./submit_info.hpp"
#include "./wait_semaphore.hpp"
#include "./signal_semaphore.hpp"
#include "./signal_fence.hpp"
#include "../__internal/function.hpp"
#include "../__instance/handle.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__fence/handle.hpp"
#include "../__device/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct queue_submit_function : vk::function<int32(*)(
		handle<vk::queue>::underlying_type queue,
		uint32 submit_count,
		const vk::submit_info* submits,
		handle<vk::fence>::underlying_type fence
	)> {
		static constexpr auto name = "vkQueueSubmit";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::queue>>.decayed == 1,
		is_range_of<is_same_as<vk::submit_info>.decayed> == 1,
		is_same_as<vk::signal_fence>.decayed <= 1
	>
	vk::result try_queue_submit(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		vk::signal_fence fence{};

		if constexpr (
			(is_same_as<vk::signal_fence>.decayed > 0).for_types<Args...>()
		) {
			fence = a.template get<is_same_as<vk::signal_fence>.decayed>();
		}

		handle<vk::queue> queue = a.template
			get<is_same_as<handle<vk::queue>>.decayed>();
		auto& submit_infos = a.template
			get<is_range_of<is_same_as<vk::submit_info>.decayed>>();

		return vk::result {
			vk::get_device_function<vk::queue_submit_function>(
				instance, device
			)(
				queue.underlying(),
				(uint32) submit_infos.size(),
				submit_infos.iterator(),
				fence.underlying()
			)
		};
	}

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::queue>>.decayed == 1,
		is_same_as<vk::submit_info>.decayed == 1,
		is_same_as<vk::signal_fence>.decayed <= 1
	>
	vk::result try_queue_submit(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		vk::signal_fence fence{};

		if constexpr (
			(is_same_as<vk::signal_fence>.decayed > 0).for_types<Args...>()
		) {
			fence = a.template get<is_same_as<vk::signal_fence>.decayed>();
		}

		handle<vk::queue> queue = a.template
			get<is_same_as<handle<vk::queue>>.decayed>();

		vk::submit_info& submit_info = a.template
			get<is_same_as<vk::submit_info>.decayed>();

		return vk::try_queue_submit(
			instance,
			device,
			queue,
			array{ submit_info },
			fence
		);
	}

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::queue>>.decayed == 1,
		is_same_as<handle<vk::command_buffer>>.decayed == 1,
		is_same_as<vk::wait_semaphore>.decayed <= 1,
		is_same_as<vk::pipeline_stages>.decayed <= 1,
		is_same_as<vk::signal_semaphore>.decayed <= 1,
		is_same_as<vk::signal_fence>.decayed <= 1
	>
	vk::result try_queue_submit(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::queue> queue = a.template
			get<is_same_as<handle<vk::queue>>.decayed>();
		
		handle<vk::command_buffer> command_buffer = a.template
			get<is_same_as<handle<vk::command_buffer>>.decayed>();

		vk::signal_fence fence{};

		if constexpr (
			(is_same_as<vk::signal_fence>.decayed > 0).for_types<Args...>()
		) {
			fence = a.template get<is_same_as<vk::signal_fence>.decayed>();
		}

		vk::submit_info si {
			.command_buffer_count = 1,
			.command_buffers = &command_buffer.underlying(),
		};

		if constexpr (
			(is_same_as<vk::wait_semaphore>.decayed > 0).for_types<Args...>()
		) {
			si.wait_semaphore_count = 1,
			si.wait_semaphores = & a.template
				get<is_same_as<vk::wait_semaphore>.decayed>().underlying();
		}

		if constexpr (
			(is_same_as<vk::signal_semaphore>.decayed > 0).for_types<Args...>()
		) {
			si.signal_semaphore_count = 1,
			si.signal_semaphores =
				(const handle<vk::semaphore>::underlying_type*)
				& a.template get<is_same_as<
					vk::signal_semaphore
				>.decayed>().underlying();
		}

		if constexpr (
			(is_same_as<vk::pipeline_stages>.decayed > 0).for_types<Args...>()
		) {
			si.wait_dst_stage_mask = & a.template
				get<is_same_as<vk::pipeline_stages>.decayed>();
		}

		return vk::try_queue_submit(
			instance, device, queue, fence, si
		);
	}

	template<typename... Args>
	void queue_submit(Args&&... args) {
		vk::result result = vk::try_queue_submit(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk