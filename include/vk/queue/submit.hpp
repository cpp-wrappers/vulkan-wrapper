#pragma once

#include "handle.hpp"
#include "wait_semaphore.hpp"
#include "signal_semaphore.hpp"
#include "submit_info.hpp"

#include "../fence/handle.hpp"
#include "../command/buffer/handle.hpp"

#include <core/range/of_value_type_same_as.hpp>

extern "C" VK_ATTR int32 VK_CALL vkQueueSubmit(
	handle<vk::queue> queue,
	uint32 submit_count,
	const vk::submit_info* submits,
	handle<vk::fence> fence
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::queue>,
		types::are_contain_range_of<vk::submit_info>,
		types::are_may_contain_one_possibly_guarded_handle_of<vk::fence>
	>::for_types<Args...>
	vk::result try_queue_submit(Args&&... args) {
		handle<vk::fence> fence{};

		if constexpr(types::are_contain_one_possibly_guarded_handle_of<vk::fence>::for_types<Args...>) {
			fence = vk::get_handle(elements::possibly_guarded_handle_of<vk::fence>(args...));
		}

		auto& queue = elements::possibly_guarded_handle_of<vk::queue>(args...);
		auto& submit_infos = elements::range_of<vk::submit_info>(args...);

		return vk::result {
			vkQueueSubmit(
				vk::get_handle(queue),
				(uint32) submit_infos.size(),
				submit_infos.data(),
				vk::get_handle(fence)
			)
		};
	}

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::queue>,
		types::are_contain_one_decayed<vk::submit_info>,
		types::are_may_contain_one_possibly_guarded_handle_of<vk::fence>
	>::for_types<Args...>
	vk::result try_queue_submit(Args&&... args) {
		handle<vk::fence> fence{};

		if constexpr(types::are_contain_one_possibly_guarded_handle_of<vk::fence>::for_types<Args...>) {
			fence = vk::get_handle(elements::possibly_guarded_handle_of<vk::fence>(args...));
		}

		auto& queue = elements::possibly_guarded_handle_of<vk::queue>(args...);
		auto& submit_info = elements::decayed<vk::submit_info>(args...);

		return vk::try_queue_submit(queue, array<vk::submit_info, 1>{ submit_info }, fence);
	}

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::queue>,
		types::are_may_contain_one_decayed<vk::wait_semaphore>,
		types::are_may_contain_one_decayed<vk::pipeline_stages>,
		types::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_may_contain_one_decayed<vk::signal_semaphore>,
		types::are_may_contain_one_possibly_guarded_handle_of<vk::fence>
	>::for_types<Args...>
	vk::result try_queue_submit(Args&&... args) {
		handle<vk::fence> fence{};

		if constexpr(types::are_contain_one_possibly_guarded_handle_of<vk::fence>::for_types<Args...>) {
			fence = vk::get_handle(elements::possibly_guarded_handle_of<vk::fence>(args...));
		}

		auto& queue = elements::possibly_guarded_handle_of<vk::queue>(args...);
		handle<vk::command_buffer> command_buffer = vk::get_handle(elements::possibly_guarded_handle_of<vk::command_buffer>(args...));

		vk::submit_info si {
			.command_buffer_count = 1,
			.command_buffers = &command_buffer,
		};

		if constexpr(types::are_contain_decayed<vk::wait_semaphore>::for_types<Args...>) {
			si.wait_semaphore_count = 1,
			si.wait_semaphores = (handle<vk::semaphore>*) &elements::decayed<vk::wait_semaphore>(args...);
		}

		if constexpr(types::are_contain_decayed<vk::signal_semaphore>::for_types<Args...>) {
			si.signal_semaphore_count = 1,
			si.signal_semaphores = (handle<vk::semaphore>*) &elements::decayed<vk::signal_semaphore>(args...);
		}

		if constexpr(types::are_contain_decayed<vk::pipeline_stages>::for_types<Args...>) {
			si.wait_dst_stage_mask = &elements::decayed<vk::pipeline_stages>(args...);
		}

		return vk::try_queue_submit(
			queue, fence, si
		);
	}

	template<typename... Args>
	void queue_submit(Args&&... args) {
		vk::result result = vk::try_queue_submit(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk