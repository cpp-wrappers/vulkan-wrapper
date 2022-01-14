#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/are_contain_range_of_value_type.hpp>

#include "../swapchain/image_index.hpp"
#include "handle.hpp"
#include "wait_semaphore.hpp"
#include "present_info.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::queue>,
		types::count_of_type<vk::present_info>::equals<1>::ignore_const::ignore_reference
	>::for_types_of<Args...>
	vk::result try_queue_present(Args&&... args) {
		auto& queue = elements::vk::possibly_guarded_handle_of<vk::queue>::for_elements_of(args...);
		auto present_info = elements::of_type<vk::present_info>::ignore_const::ignore_reference::for_elements_of(args...);

		return {
			(int32) vkQueuePresentKHR(
				(VkQueue) vk::get_handle_value(queue),
				(VkPresentInfoKHR*) &present_info
			)
		};
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::queue>,
		types::count_of_ranges_of_value_type<vk::wait_semaphore>::equals<1>,
		types::count_of_ranges_of_value_type<vk::handle<vk::swapchain>>::equals<1>,
		types::count_of_ranges_of_value_type<vk::image_index>::equals<1>,
		types::count_of_ranges_of_value_type<vk::result>::less_or_equals<1>
	>::for_types_of<Args...>
	vk::result try_queue_present(Args&&... args) {
		auto& queue = elements::vk::possibly_guarded_handle_of<vk::queue>::for_elements_of(args...);
		auto& wait_semaphores = elements::range_of_value_type<vk::wait_semaphore>::for_elements_of(args...);
		auto& swapchains = elements::range_of_value_type<vk::handle<vk::swapchain>>::for_elements_of(args...);
		auto& image_indices = elements::range_of_value_type<vk::image_index>::for_elements_of(args...);

		vk::present_info present_info {
			.wait_semaphore_count = (uint32) wait_semaphores.size(),
			.wait_semaphores = wait_semaphores.data(),
			.swapchain_count = (uint32) swapchains.size(),
			.swapchains = swapchains.data(),
			.image_indices = image_indices.data()
		};

		if constexpr(types::are_contain_range_of_value_type<vk::result>::for_types_of<Args...>) {
			present_info.results = elements::range_of_value_type<vk::result>::for_elements_of(args...);
		}
	
		return vk::try_queue_present(queue, present_info);
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::queue>,
		types::count_of_type<vk::wait_semaphore>::equals<1>::ignore_const::ignore_reference,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::swapchain>,
		types::count_of_type<vk::image_index>::equals<1>::ignore_const::ignore_reference,
		types::count_of_type<vk::result&>::less_or_equals<1>
	>::for_types_of<Args...>
	vk::result try_queue_present(Args&&... args) {
		auto& queue = elements::vk::possibly_guarded_handle_of<vk::queue>::for_elements_of(args...);

		vk::handle<vk::semaphore> wait_semaphore =
			(vk::handle<vk::semaphore>) elements::of_type<vk::wait_semaphore>::ignore_const::ignore_reference::for_elements_of(args...);
		
		auto& swapchain = elements::vk::possibly_guarded_handle_of<vk::swapchain>::for_elements_of(args...);
		vk::image_index image_index = elements::of_type<vk::image_index>::ignore_const::ignore_reference::for_elements_of(args...);

		vk::present_info present_info {
			.wait_semaphore_count = 1,
			.wait_semaphores = &wait_semaphore,
			.swapchain_count = 1,
			.swapchains = &vk::get_handle(swapchain),
			.image_indices = &image_index
		};

		if constexpr(types::are_contain_type<vk::result&>::for_types_of<Args...>) {
			present_info.results = & elements::of_type<vk::result&>::for_elements_of(args...);
		}
	
		return vk::try_queue_present(queue, present_info);
	}

	template<typename... Args>
	void queue_present(Args&&... args) {
		vk::result result = vk::try_queue_present(forward<Args>(args)...);
		if(result.success()) throw result;
	}

} // vk