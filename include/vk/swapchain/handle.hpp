#pragma once

#include <core/forward.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/for_each_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/one_of.hpp>
#include <core/exchange.hpp>
#include <core/type/range.hpp>
#include <core/span.hpp>

#include "image_index.hpp"
#include "timeout.hpp"
#include "../shared/headers.hpp"
#include "../shared/result.hpp"
#include "../shared/count.hpp"
#include "../semaphore/handle.hpp"
#include "../fence/handle.hpp"
#include "../device/handle.hpp"
#include "../image/handle.hpp"

namespace vk {

	class device;
	class semaphore;
	class fence;
	class image;

	struct swapchain {
		uint64 handle;

		elements::one_of<vk::result, vk::image_index>
		try_acquire_next_image(vk::device device, vk::timeout timeout, vk::semaphore semaphore = {VK_NULL_HANDLE}, vk::fence fence = {VK_NULL_HANDLE}) {
			uint32 index;

			vk::result result {
				(uint32) vkAcquireNextImageKHR(
					(VkDevice) device.handle ,
					(VkSwapchainKHR) handle,
					(uint64) timeout,
					(VkSemaphore) semaphore.handle,
					(VkFence) fence.handle,
					&index
				)
			};

			if(result.success()) return vk::image_index{ index };
			return result;
		}

		elements::one_of<vk::result, vk::count>
		try_get_images(vk::device device, type::range_of_value_type<vk::image> auto&& images) const {
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

		template<type::range_of_value_type<vk::image> Images>
		vk::count get_images(vk::device device, Images&& images) const {
			return try_get_images(device, forward<Images>(images)).template get<vk::count>();
		}

		elements::one_of<vk::result, vk::count> try_get_image_count(vk::device device) const {
			return try_get_images(device, span<vk::image>{ nullptr, 0 });
		}

		vk::count get_image_count(vk::device device) const {
			return try_get_image_count(device).get<vk::count>();
		}

		elements::one_of<vk::result, vk::count>
		try_view_images(vk::device device, vk::count count, auto&& f) const {
			vk::image images[(uint32)count];
			auto result = try_get_images(device, span{ images, (uint32)count });
			if(result.is_current<vk::result>()) return result.get<vk::result>();
			count = result.get<vk::count>();
			f(span{ images, (uint32)count } );
			return count;
		}

		elements::one_of<vk::result, vk::count>
		try_for_each_image(vk::device device, vk::count count, auto&& f) const {
			return try_view_images(device, count, [&](auto view) {
				for(vk::image image : view) {
					f(image);
				}
			});
		}

		template<typename F>
		elements::one_of<vk::result, vk::count>
		try_for_each_image(vk::device device, F&& f) const {
			return try_for_feach_image(device, get_image_count(device), forward<F>(f));
		}

		template<typename F>
		vk::count for_each_image(vk::device device, F&& f) const {
			return try_for_each_image(device, get_image_count(device), forward<F>(f));
		}
	}; // swapchain

} // vk

