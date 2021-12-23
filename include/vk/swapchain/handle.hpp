#pragma once

#include <core/forward.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/for_each_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/one_of.hpp>
#include <core/exchange.hpp>
#include <core/range/of_value_type.hpp>
#include <core/span.hpp>

#include "image_index.hpp"
#include "timeout.hpp"
#include "../shared/headers.hpp"
#include "../shared/result.hpp"
#include "../shared/count.hpp"
#include "../shared/guarded_handle.hpp"
#include "../shared/handle.hpp"

namespace vk {

	struct device;
	struct semaphore;
	struct fence;
	struct image;

	struct swapchain;

	template<>
	struct vk::handle<vk::swapchain> : vk::handle_base<vk::non_dispatchable> {

		elements::one_of<vk::result, vk::image_index>
		try_acquire_next_image(
			const vk::ordinary_or_guarded_handle<vk::device> auto& device,
			vk::timeout timeout,
			const vk::ordinary_or_guarded_handle<vk::semaphore> auto& semaphore,
			const vk::ordinary_or_guarded_handle<vk::fence> auto& fence
		) const {
			uint32 index;

			vk::result result {
				(int32) vkAcquireNextImageKHR(
					(VkDevice) vk::get_handle_value(device),
					(VkSwapchainKHR) value,
					(uint64) timeout,
					(VkSemaphore) vk::get_handle_value(semaphore),
					(VkFence) vk::get_handle_value(fence),
					&index
				)
			};

			if(result.success()) return vk::image_index{ index };

			return result;
		}

		elements::one_of<vk::result, vk::count>
		try_get_images(
			vk::ordinary_or_guarded_handle<vk::device> auto& device,
			range::of_value_type<vk::handle<vk::image>> auto&& images
		) const {
			uint32 count = images.size();

			vk::result result {
				(int32) vkGetSwapchainImagesKHR(
					(VkDevice) vk::get_handle_value(device),
					(VkSwapchainKHR) value,
					&count,
					(VkImage*) images.data()
				)
			};

			if(result.success()) return vk::count{ count };
			return result;
		}

		template<
			vk::ordinary_or_guarded_handle<vk::device> Device,
			range::of_value_type<vk::image> Images
		>
		vk::count get_images(Device& device, Images&& images) const {
			auto result = try_get_images(device, forward<Images>(images));
			if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
			return result.template get<vk::count>();
		}

		elements::one_of<vk::result, vk::count>
		try_get_image_count(const vk::ordinary_or_guarded_handle<vk::device> auto& device) const {
			return try_get_images(device, span<vk::handle<vk::image>>{ nullptr, 0 });
		}

		vk::count get_image_count(const vk::ordinary_or_guarded_handle<vk::device> auto& device) const {
			auto result = try_get_image_count(device);
			if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
			return result.template get<vk::count>();
		}

		elements::one_of<vk::result, vk::count>
		try_view_images(const vk::ordinary_or_guarded_handle<vk::device> auto& device, vk::count count, auto&& f) const;

		elements::one_of<vk::result, vk::count>
		try_for_each_image(const vk::ordinary_or_guarded_handle<vk::device> auto& device, vk::count count, auto&& f) const {
			return try_view_images(forward<vk::device>(device), count, [&](auto view) {
				for(vk::image image : view) {
					f(image);
				}
			});
		}

		template<typename F>
		elements::one_of<vk::result, vk::count>
		try_for_each_image(vk::ordinary_or_guarded_handle<vk::device> auto& device, F&& f) const {
			auto result = try_get_image_count(device);
			if(result.template is_current<vk::result>()) return result;
			return try_for_feach_image(device, result.template get<vk::count>(), forward<F>(f));
		}

		template<typename F>
		vk::count for_each_image(vk::ordinary_or_guarded_handle<vk::device> auto& device, F&& f) const {
			auto result = try_for_each_image(device, forward<F>(f));
			if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
			return result.template get<vk::count>();
		}
	}; // swapchain

} // vk

#include "../image/handle.hpp"

elements::one_of<vk::result, vk::count>
vk::handle<vk::swapchain>::try_view_images(const vk::ordinary_or_guarded_handle<vk::device> auto& device, vk::count count, auto&& f) const {
	vk::handle<vk::image> images[(uint32)count];
	auto result = try_get_images(device, span{ images, (uint32)count });
	if(result.template is_current<vk::result>()) return result.template get<vk::result>();
	count = result.template get<vk::count>();
	f(span{ images, (uint32)count } );
	return count;
}