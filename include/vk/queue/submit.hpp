#pragma once

#include "handle.hpp"
#include "wait_semaphore.hpp"
#include "signal_semaphore.hpp"
#include "submit_info.hpp"
#include "../fence/handle.hpp"
#include "../command/buffer/handle.hpp"

#include <core/range/of_value_type.hpp>

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::queue>,
		types::count_of_ranges_of_value_type<vk::submit_info>::equals<1>,
		types::vk::are_may_contain_one_possibly_guarded_handle_of<vk::fence>
	>::for_types<Args...>
	vk::result try_queue_submit(Args&&... args) {
		vk::handle<vk::fence> fence{};

		if constexpr(types::vk::are_contain_one_possibly_guarded_handle_of<vk::fence>::for_types<Args...>) {
			fence = vk::get_handle(elements::vk::possibly_guarded_handle_of<vk::fence>(args...));
		}

		auto& queue = elements::vk::possibly_guarded_handle_of<vk::queue>(args...);
		auto& submit_infos = elements::range_of_value_type<vk::submit_info>(args...);

		return vk::result {
			(int32)vkQueueSubmit(
				(VkQueue) vk::get_handle_value(queue),
				(uint32) submit_infos.size(),
				(VkSubmitInfo*) submit_infos.data(),
				(VkFence) vk::get_handle_value(fence)
			)
		};
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::queue>,
		types::are_contain_one_decayed_same_as<vk::submit_info>,
		types::vk::are_may_contain_one_possibly_guarded_handle_of<vk::fence>
	>::for_types<Args...>
	vk::result try_queue_submit(Args&&... args) {
		vk::handle<vk::fence> fence{};

		if constexpr(types::vk::are_contain_one_possibly_guarded_handle_of<vk::fence>::for_types<Args...>) {
			fence = vk::get_handle(elements::vk::possibly_guarded_handle_of<vk::fence>(args...));
		}

		auto& queue = elements::vk::possibly_guarded_handle_of<vk::queue>(args...);
		auto& submit_info = elements::decayed_same_as<vk::submit_info>(args...);

		return vk::try_queue_submit(queue, array<vk::submit_info, 1>{ submit_info }, fence);
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::queue>,
		types::are_may_contain_one_decayed_same_as<vk::wait_semaphore>,
		types::are_may_contain_one_decayed_same_as<vk::pipeline_stages>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_may_contain_one_decayed_same_as<vk::signal_semaphore>,
		types::vk::are_may_contain_one_possibly_guarded_handle_of<vk::fence>
	>::for_types<Args...>
	vk::result try_queue_submit(Args&&... args) {
		vk::handle<vk::fence> fence{};

		if constexpr(types::vk::are_contain_one_possibly_guarded_handle_of<vk::fence>::for_types<Args...>) {
			fence = vk::get_handle(elements::vk::possibly_guarded_handle_of<vk::fence>(args...));
		}

		auto& queue = elements::vk::possibly_guarded_handle_of<vk::queue>(args...);
		vk::handle<vk::command_buffer> command_buffer = vk::get_handle(elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...));

		vk::submit_info si {
			.command_buffer_count = 1,
			.command_buffers = &command_buffer,
		};

		if constexpr(types::are_contain_decayed_same_as<vk::wait_semaphore>::for_types<Args...>) {
			si.wait_semaphore_count = 1,
			si.wait_semaphores = (vk::handle<vk::semaphore>*) &elements::decayed_same_as<vk::wait_semaphore>(args...);
		}

		if constexpr(types::are_contain_decayed_same_as<vk::signal_semaphore>::for_types<Args...>) {
			si.signal_semaphore_count = 1,
			si.signal_semaphores = (vk::handle<vk::semaphore>*) &elements::decayed_same_as<vk::signal_semaphore>(args...);
		}

		if constexpr(types::are_contain_decayed_same_as<vk::pipeline_stages>::for_types<Args...>) {
			si.wait_dst_stage_mask = &elements::decayed_same_as<vk::pipeline_stages>(args...);
		}

		return vk::try_queue_submit(
			queue, fence, si
		);
	}

	template<typename... Args>
	void queue_submit(Args&&... args) {
		vk::result result = vk::try_queue_submit(forward<Args>(args)...);
		if(result.error()) default_unexpected_handler(result);
	}

} // vk