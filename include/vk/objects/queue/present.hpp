#pragma once

#include "handle.hpp"
#include "wait_semaphore.hpp"
#include "present_info.hpp"
#include "../swapchain/image_index.hpp"

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/meta/types/are_contain_range_of_value_type.hpp>

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::queue>,
		types::are_contain_one_decayed_same_as<vk::present_info>
	>::for_types<Args...>
	vk::result try_queue_present(Args&&... args) {
		auto& queue = elements::vk::possibly_guarded_handle_of<vk::queue>(args...);
		auto present_info = elements::decayed_same_as<vk::present_info>(args...);

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
	>::for_types<Args...>
	vk::result try_queue_present(Args&&... args) {
		auto& queue = elements::vk::possibly_guarded_handle_of<vk::queue>(args...);
		auto& wait_semaphores = elements::range_of_value_type<vk::wait_semaphore>(args...);
		auto& swapchains = elements::range_of_value_type<vk::handle<vk::swapchain>>(args...);
		auto& image_indices = elements::range_of_value_type<vk::image_index>(args...);

		vk::present_info present_info {
			.wait_semaphore_count = (uint32) wait_semaphores.size(),
			.wait_semaphores = wait_semaphores.data(),
			.swapchain_count = (uint32) swapchains.size(),
			.swapchains = swapchains.data(),
			.image_indices = image_indices.data()
		};

		if constexpr(types::are_contain_range_of_value_type<vk::result>::for_types<Args...>) {
			present_info.results = elements::range_of_value_type<vk::result>(args...);
		}
	
		return vk::try_queue_present(queue, present_info);
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::queue>,
		types::are_contain_one_decayed_same_as<vk::wait_semaphore>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::swapchain>,
		types::are_contain_one_decayed_same_as<vk::image_index>,
		types::are_may_contain_one_decayed_same_as<vk::result&> // TODO
	>::for_types<Args...>
	vk::result try_queue_present(Args&&... args) {
		auto& queue = elements::vk::possibly_guarded_handle_of<vk::queue>(args...);

		vk::handle<vk::semaphore> wait_semaphore =
			(vk::handle<vk::semaphore>) elements::decayed_same_as<vk::wait_semaphore>(args...);
		
		auto& swapchain = elements::vk::possibly_guarded_handle_of<vk::swapchain>(args...);
		vk::image_index image_index = elements::decayed_same_as<vk::image_index>(args...);

		vk::present_info present_info {
			.wait_semaphore_count = 1,
			.wait_semaphores = &wait_semaphore,
			.swapchain_count = 1,
			.swapchains = &vk::get_handle(swapchain),
			.image_indices = &image_index
		};

		if constexpr(types::are_contain_decayed_same_as<vk::result&>::for_types<Args...>) {
			present_info.results = & elements::decayed_same_as<vk::result&>(args...);
		}
	
		return vk::try_queue_present(queue, present_info);
	}

	template<typename... Args>
	void queue_present(Args&&... args) {
		vk::result result = vk::try_queue_present(forward<Args>(args)...);
		if(result.error()) default_unexpected_handler(result);
	}

} // vk