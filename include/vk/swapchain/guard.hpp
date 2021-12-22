#pragma once

#include "handle.hpp"
#include "create.hpp"
#include "../device/handle.hpp"
#include "../shared/guarded.hpp"

namespace vk {

	template<>
	class guarded<vk::swapchain> {
		vk::handle<vk::swapchain> swapchain;
		vk::handle<vk::device> m_device;
	public:

		guarded<vk::swapchain>(vk::handle<vk::swapchain> swapchain, vk::handle<vk::device> device)
			: swapchain{ swapchain }, m_device{ device }
		{}

		~guarded<vk::swapchain>() {
			if(swapchain.value) {
				vkDestroySwapchainKHR(
					(VkDevice) m_device.value,
					(VkSwapchainKHR) exchange(swapchain.value, 0),
					nullptr
				);
			}
		}

		const vk::handle<vk::swapchain>& object() const {
			return swapchain;
		}

		const vk::handle<vk::device>& device() const {
			return m_device;
		}

		elements::one_of<vk::result, vk::image_index>
		try_acquire_next_image(
			vk::timeout timeout,
			vk::handle<vk::semaphore> semaphore = { VK_NULL_HANDLE },
			vk::handle<vk::fence> fence = {VK_NULL_HANDLE}
		) {
			return swapchain.try_acquire_next_image(m_device, timeout, semaphore, fence);
		}

		template<range::of_value_type<vk::handle<vk::image>> Images>
		vk::count get_images(Images&& images) const {
			return swapchain.get_images(m_device, forward<Images>(images));
		}

		vk::count get_image_count() const {
			return swapchain.get_image_count(m_device);
		}

		template<typename F>
		vk::count for_each_image(F&& f) const {
			return swapchain.for_each_image(m_device, forward<F>(f));
		}
	};
}