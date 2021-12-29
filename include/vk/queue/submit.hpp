#pragma once

#include "handle.hpp"
#include "wait_semaphore.hpp"
#include "signal_semaphore.hpp"
#include "../fence/handle.hpp"

namespace vk {

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::contain_one<vk::queue>,
			types::count_of_ranges_of_value_type<vk::submit_info>::equals<1>,
			types::vk::may_contain_one<vk::fence>
		>::for_types_of<Args...>
	)
	vk::result try_queue_submit(Args&&... args) {
		vk::handle<vk::fence> fence{};

		if constexpr(types::vk::contain_one<vk::fence>::for_types_of<Args...>) {
			fence = vk::get_handle(elements::vk::of_type<vk::fence>::for_elements_of(args...));
		}

		auto& queue = elements::vk::of_type<vk::queue>::for_elements_of(args...);
		auto& submit_infos = elements::range_of_value_type<vk::submit_info>::for_elements_of(args...);

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
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::contain_one<vk::queue>,
			types::count_of_type<vk::submit_info>::equals<1>::ignore_const::ignore_reference,
			types::vk::may_contain_one<vk::fence>
		>::for_types_of<Args...>
	)
	vk::result try_queue_submit(Args&&... args) {
		vk::handle<vk::fence> fence{};

		if constexpr(types::vk::contain_one<vk::fence>::for_types_of<Args...>) {
			fence = vk::get_handle(elements::vk::of_type<vk::fence>::for_elements_of(args...));
		}

		auto& queue = elements::vk::of_type<vk::queue>::for_elements_of(args...);
		auto& submit_info = elements::of_type<vk::submit_info>::ignore_const::ignore_reference::for_elements_of(args...);

		return vk::try_queue_submit(queue, array{ submit_info }, fence);
	}

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::contain_one<vk::queue>,
			types::count_of_type<vk::wait_semaphore>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::pipeline_stages>::equals<1>::ignore_const::ignore_reference,
			types::vk::contain_one<vk::command_buffer>,
			types::count_of_type<vk::signal_semaphore>::equals<1>::ignore_const::ignore_reference,
			types::vk::may_contain_one<vk::fence>
		>::for_types_of<Args...>
	)
	vk::result try_queue_submit(Args&&... args) {
		vk::handle<vk::fence> fence{};

		if constexpr(types::vk::contain_one<vk::fence>::for_types_of<Args...>) {
			fence = vk::get_handle(elements::vk::of_type<vk::fence>::for_elements_of(args...));
		}

		auto& queue = elements::vk::of_type<vk::queue>::for_elements_of(args...);
		vk::handle<vk::command_buffer> command_buffer = vk::get_handle(elements::vk::of_type<vk::command_buffer>::for_elements_of(args...));
		vk::handle<vk::semaphore> wait_semaphore = (vk::handle<vk::semaphore>)elements::of_type<vk::wait_semaphore>::ignore_const::ignore_reference::for_elements_of(args...);
		vk::handle<vk::semaphore> signal_semaphore = (vk::handle<vk::semaphore>)elements::of_type<vk::signal_semaphore>::ignore_const::ignore_reference::for_elements_of(args...);

		vk::pipeline_stages wait_dst_stage_mask = elements::of_type<vk::pipeline_stages>::ignore_const::ignore_reference::for_elements_of(args...);

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
		if(!result.success()) throw result;
	}
}