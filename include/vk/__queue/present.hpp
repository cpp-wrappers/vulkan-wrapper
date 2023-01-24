#pragma once

extern "C" VK_ATTR int32 VK_CALL vkQueuePresentKHR(
	handle<vk::queue>       queue,
	const vk::present_info* present_info
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::queue>>,
		types::are_contain_one_decayed<vk::present_info>
	>::for_types<Args...>
	vk::result try_queue_present(Args&&... args) {
		auto queue = elements::decayed<handle<vk::queue>>(args...);
		auto present_info = elements::decayed<vk::present_info>(args...);

		return {
			vkQueuePresentKHR(
				queue,
				&present_info
			)
		};
	}

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::queue>>,
		types::are_contain_range_of<vk::wait_semaphore>,
		types::are_contain_range_of<handle<vk::swapchain>>,
		types::are_contain_range_of<vk::image_index>,
		types::are_may_contain_range_of<vk::result>
	>::for_types<Args...>
	vk::result try_queue_present(Args&&... args) {
		auto queue = elements::decayed<handle<vk::queue>>(args...);
		auto& wait_semaphores = elements::range_of<vk::wait_semaphore>(args...);
		auto& swapchains = elements::range_of<handle<vk::swapchain>>(args...);
		auto& image_indices = elements::range_of<vk::image_index>(args...);

		vk::present_info present_info {
			.wait_semaphore_count = (uint32) wait_semaphores.size(),
			.wait_semaphores = wait_semaphores.data(),
			.swapchain_count = (uint32) swapchains.size(),
			.swapchains = swapchains.data(),
			.image_indices = image_indices.data()
		};

		if constexpr (
			types::are_contain_range_of<vk::result>::for_types<Args...>
		) { present_info.results = elements::range_of<vk::result>(args...); }
	
		return vk::try_queue_present(queue, present_info);
	}

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::queue>>,
		types::are_contain_one_decayed<vk::wait_semaphore>,
		types::are_contain_one_decayed<handle<vk::swapchain>>,
		types::are_contain_one_decayed<vk::image_index>
	>::for_types<Args...>
	vk::result try_queue_present(Args&&... args) {
		auto queue = elements::decayed<handle<vk::queue>>(args...);

		auto wait_semaphore =
			(handle<vk::semaphore>)
			elements::decayed<vk::wait_semaphore>(args...);
		
		auto swapchain = elements::decayed<handle<vk::swapchain>>(args...);
		vk::image_index image_index = elements::decayed<vk::image_index>(args...);

		vk::present_info present_info {
			.wait_semaphore_count = 1,
			.wait_semaphores = &wait_semaphore,
			.swapchain_count = 1,
			.swapchains = &swapchain,
			.image_indices = &image_index
		};

		return vk::try_queue_present(queue, present_info);
	}

	template<typename... Args>
	void queue_present(Args&&... args) {
		vk::result result = vk::try_queue_present(forward<Args>(args)...);
		if(result.error()) vk::unexpected_handler(result);
	}

} // vk