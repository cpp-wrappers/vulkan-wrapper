#pragma once

#include "image_index.hpp"

#include <core/span.hpp>
#include <core/forward.hpp>
#include <core/exchange.hpp>
#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/elements/one_of.hpp>

#include "vk/semaphore/handle.hpp"
#include "vk/fence/handle.hpp"
#include "vk/timeout.hpp"
#include "vk/headers.hpp"
#include "vk/result.hpp"
#include "vk/count.hpp"
#include <core/handle/possibly_guarded_of.hpp>
#include "vk/handle/get_value.hpp"

namespace vk {

	struct device;
	struct semaphore;
	struct fence;
	struct image;

	struct swapchain;

} // vk

template<>
struct handle<vk::swapchain> : vk::handle_base<vk::non_dispatchable> {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_may_contain_one_possibly_guarded_handle_of<vk::semaphore>,
		types::are_may_contain_one_possibly_guarded_handle_of<vk::fence>,
		types::are_may_contain_one_decayed<vk::timeout>
	>::for_types<Args...>
	vk::expected<vk::image_index>
	acquire_next_image(Args&&... args) const {
		auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);
		
		vk::timeout timeout{ UINT64_MAX };

		if constexpr(types::are_contain_decayed<vk::timeout>::for_types<Args...>) {
			timeout = elements::decayed<vk::timeout>(args...);
		}

		handle<vk::semaphore> semaphore{ VK_NULL_HANDLE };

		if constexpr(types::are_contain_one_possibly_guarded_handle_of<vk::semaphore>::for_types<Args...>) {
			semaphore = vk::get_handle(elements::possibly_guarded_handle_of<vk::semaphore>(args...));
		}

		handle<vk::fence> fence{ VK_NULL_HANDLE };

		if constexpr(types::are_contain_one_possibly_guarded_handle_of<vk::fence>::for_types<Args...>) {
			fence = vk::get_handle(elements::possibly_guarded_handle_of<vk::fence>(args...));
		}

		uint32 index;

		vk::result result {
			(int32) vkAcquireNextImageKHR(
				(VkDevice) vk::get_handle_value(device),
				(VkSwapchainKHR) vk::get_handle_value(*this),
				(uint64) timeout,
				(VkSemaphore) vk::get_handle_value(semaphore),
				(VkFence) vk::get_handle_value(fence),
				&index
			)
		};

		if(result.error()) return result;

		return vk::image_index{ index };
	}

	vk::expected<vk::count>
	get_images(
		possibly_guarded_handle_of<vk::device> auto& device,
		range::of<handle<vk::image>> auto&& images
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
		if(result.error()) return result;
		return vk::count{ count };
	}
	vk::expected<vk::count>
	get_image_count(const possibly_guarded_handle_of<vk::device> auto& device) const {
		return get_images(device, span<handle<vk::image>>{ nullptr, 0 });
	}
	vk::expected<vk::count>
	view_images(const possibly_guarded_handle_of<vk::device> auto& device, vk::count count, auto&& f) const;
	vk::expected<vk::count>
	for_each_image(const possibly_guarded_handle_of<vk::device> auto& device, vk::count count, auto&& f) const {
		return view_images(forward<vk::device>(device), count, [&](auto view) {
			for(vk::image image : view) {
				f(image);
			}
		});
	}
	template<typename F>
	vk::expected<vk::count>
	for_each_image(possibly_guarded_handle_of<vk::device> auto& device, F&& f) const {
		vk::expected<vk::count> result = get_image_count(device);
		if(result.is_unexpected()) return result;
		return try_for_feach_image(
			device,
			result.get_expected(),
			forward<F>(f)
		);
	}
}; // swapchain

#include "../image/handle.hpp"

vk::expected<vk::count>
handle<vk::swapchain>::view_images(const possibly_guarded_handle_of<vk::device> auto& device, vk::count count, auto&& f) const {
	handle<vk::image> images[(uint32)count];
	vk::expected<vk::count> result = get_images(device, span{ images, (uint32)count });
	if(result.is_unexpected()) return result;
	count = result.get_expected();
	f(span{ images, (uint32)count } );
	return count;
}