#pragma once

#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/types/are_contain_one_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>

#include "../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../types/are_may_contain_one_possibly_guarded_handle_of.hpp"
#include "../fence/handle.hpp"
#include "../command/buffer/handle.hpp"
#include "wait_semaphore.hpp"
#include "signal_semaphore.hpp"
#include "submit_info.hpp"
#include "handle.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::queue>,
		types::count_of_ranges_of_value_type<vk::submit_info>::equals<1>,
		types::vk::are_may_contain_one_possibly_guarded_handle_of<vk::fence>
	>::for_types_of<Args...>
	vk::result try_queue_submit(Args&&... args) {
		vk::handle<vk::fence> fence{};

		if constexpr(types::vk::are_contain_one_possibly_guarded_handle_of<vk::fence>::for_types_of<Args...>) {
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
		types::are_contain_one_type<vk::submit_info>,
		types::vk::are_may_contain_one_possibly_guarded_handle_of<vk::fence>
	>::for_types_of<decay<Args>...>
	vk::result try_queue_submit(Args&&... args) {
		vk::handle<vk::fence> fence{};

		if constexpr(types::vk::are_contain_one_possibly_guarded_handle_of<vk::fence>::for_types_of<Args...>) {
			fence = vk::get_handle(elements::vk::possibly_guarded_handle_of<vk::fence>(args...));
		}

		auto& queue = elements::vk::possibly_guarded_handle_of<vk::queue>(args...);
		auto& submit_info = elements::of_type<vk::submit_info>(args...);

		return vk::try_queue_submit(queue, array<vk::submit_info, 1>{ submit_info }, fence);
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::queue>,
		types::are_contain_one_type<vk::wait_semaphore>,
		types::are_contain_one_type<vk::pipeline_stages>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_contain_one_type<vk::signal_semaphore>,
		types::vk::are_may_contain_one_possibly_guarded_handle_of<vk::fence>
	>::for_types_of<decay<Args>...>
	vk::result try_queue_submit(Args&&... args) {
		vk::handle<vk::fence> fence{};

		if constexpr(types::vk::are_contain_one_possibly_guarded_handle_of<vk::fence>::for_types_of<Args...>) {
			fence = vk::get_handle(elements::vk::possibly_guarded_handle_of<vk::fence>(args...));
		}

		auto& queue = elements::vk::possibly_guarded_handle_of<vk::queue>(args...);
		vk::handle<vk::command_buffer> command_buffer = vk::get_handle(elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...));
		vk::handle<vk::semaphore> wait_semaphore = (vk::handle<vk::semaphore>)elements::of_type<vk::wait_semaphore>(args...);
		vk::handle<vk::semaphore> signal_semaphore = (vk::handle<vk::semaphore>)elements::of_type<vk::signal_semaphore>(args...);

		vk::pipeline_stages wait_dst_stage_mask = elements::of_type<vk::pipeline_stages>(args...);

		return vk::try_queue_submit(
			queue, fence,
			vk::submit_info {
				.wait_semaphore_count = 1,
				.wait_semaphores = &wait_semaphore,
				.wait_dst_stage_mask = &wait_dst_stage_mask,
				.command_buffer_count = 1,
				.command_buffers = &command_buffer,
				.signal_semaphore_count = 1,
				.signal_semaphores = &signal_semaphore
			}
		);
	}

	template<typename... Args>
	void queue_submit(Args&&... args) {
		vk::result result = vk::try_queue_submit(forward<Args>(args)...);
		if(result.error()) default_unexpected_handler(result);
	}

} // vk