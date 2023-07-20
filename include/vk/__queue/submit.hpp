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
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::queue>> == 1,
		count_of_range_of_decayed<vk::submit_info> == 1,
		count_of_decayed_same_as<vk::signal_fence> <= 1
	>
	vk::result try_queue_submit(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		vk::signal_fence fence{};

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::signal_fence> > 0
		) {
			fence = a.template get_decayed_same_as<vk::signal_fence>();
		}

		handle<vk::queue> queue = a.template
			get_decayed_same_as<handle<vk::queue>>();
		auto& submit_infos = a.template get_range_of_decayed<vk::submit_info>();

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
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::queue>> == 1,
		count_of_decayed_same_as<vk::submit_info> == 1,
		count_of_decayed_same_as<vk::signal_fence> <= 1
	>
	vk::result try_queue_submit(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		vk::signal_fence fence{};

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::signal_fence> > 0
		) {
			fence = a.template get_decayed_same_as<vk::signal_fence>();
		}

		handle<vk::queue> queue = a.template
			get_decayed_same_as<handle<vk::queue>>();

		vk::submit_info& submit_info = a.template
			get_decayed_same_as<vk::submit_info>();

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
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::queue>> == 1,
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<vk::wait_semaphore> <= 1,
		count_of_decayed_same_as<vk::pipeline_stages> <= 1,
		count_of_decayed_same_as<vk::signal_semaphore> <= 1,
		count_of_decayed_same_as<vk::signal_fence> <= 1
	>
	vk::result try_queue_submit(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::queue> queue = a.template
			get_decayed_same_as<handle<vk::queue>>();
		
		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		vk::signal_fence fence{};

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::signal_fence> > 0
		) {
			fence = a.template get_decayed_same_as<vk::signal_fence>();
		}

		vk::submit_info si {
			.command_buffer_count = 1,
			.command_buffers = &command_buffer.underlying(),
		};

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::wait_semaphore> > 0
		) {
			si.wait_semaphore_count = 1,
			si.wait_semaphores = & a.template
				get_decayed_same_as<vk::wait_semaphore>().underlying();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::signal_semaphore> > 0
		) {
			si.signal_semaphore_count = 1,
			si.signal_semaphores =
				(const handle<vk::semaphore>::underlying_type*)
				& a.template get_decayed_same_as<
					vk::signal_semaphore
				>().underlying();
		}

		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::pipeline_stages> > 0
		) {
			si.wait_dst_stage_mask = & a.template
				get_decayed_same_as<vk::pipeline_stages>();
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