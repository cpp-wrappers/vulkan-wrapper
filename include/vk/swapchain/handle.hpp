#pragma once

#include <core/forward.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/for_each_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/one_of.hpp>
#include <core/exchange.hpp>
#include <core/type/range.hpp>

#include "image_index.hpp"
#include "timeout.hpp"
#include "../shared/headers.hpp"
#include "../shared/result.hpp"
#include "../shared/count.hpp"
#include "../semaphore/handle.hpp"
#include "../fence/fence.hpp"
#include "../device/handle.hpp"

namespace vk {

	class device;
	class semaphore;
	class fence;
	class image;

	struct swapchain {
		uint64 handle;

		elements::one_of<vk::result, vk::image_index>
		try_acquire_next_image(vk::device device, vk::timeout timeout, vk::semaphore* semaphore = {}, vk::fence* fence = {}) {
			uint32 index;

			vk::result result {
				(uint32) vkAcquireNextImageKHR(
					(VkDevice) device.handle ,
					(VkSwapchainKHR) handle,
					(uint64) timeout,
					(VkSemaphore) semaphore->handle,
					(VkFence) fence->handle,
					&index
				)
			};

			if(result.success()) return vk::image_index{ index };
			return result;
		}

		elements::one_of<vk::result, vk::count>
		try_get_images(vk::device device, type::range_of_value_type<uint64> auto&& images) const {
			uint32 count = images.size();

			vk::result result {
				(uint32) vkGetSwapchainImagesKHR(
					(VkDevice) device.handle,
					(VkSwapchainKHR) handle,
					&count,
					(VkImage*) images.data()
				)
			};

			if(result.success()) return vk::count{ count };
			return result;
		}
	}; // swapchain

} // vk

