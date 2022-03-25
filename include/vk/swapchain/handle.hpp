#pragma once

#include "image_index.hpp"

#include "../semaphore/handle.hpp"
#include "../fence/handle.hpp"
#include "../timeout.hpp"
#include "../headers.hpp"
#include "../result.hpp"
#include "../count.hpp"
#include "../handle/get_value.hpp"
#include "../image/handle.hpp"

#include <core/span.hpp>
#include <core/forward.hpp>
#include <core/exchange.hpp>
#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/elements/one_of.hpp>
#include <core/handle/possibly_guarded_of.hpp>

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
	vk::expected<vk::image_index> try_acquire_next_image(Args&&...) const;

	template<typename... Args>
	vk::count get_images(Args&&...) const;

	template<possibly_guarded_handle_of<vk::device> Device>
	vk::count get_image_count(Device&& device) const {
		return get_images(device, span<handle<vk::image>>{ nullptr, 0 });
	}

	template<possibly_guarded_handle_of<vk::device> Device>
	decltype(auto)
	view_images(Device&& device, vk::count count, auto&& f) const {
		handle<vk::image> images[(uint32)count];
		count = get_images(device, span{ images, (uint32)count });
		return f(span{ images, (uint32)count });
	}

	template<possibly_guarded_handle_of<vk::device> Device, typename F>
	decltype(auto)
	view_images(Device&& device, F&& f) const {
		auto count = get_image_count(device);
		return view_images(device, count, forward<F>(f));
	}

	template<possibly_guarded_handle_of<vk::device> Device>
	void for_each_image(Device&& device, vk::count count, auto&& f) const {
		view_images(forward<Device>(device), count, [&](auto view) {
			for(handle<vk::image> image : view) {
				f(image);
			}
		});
	}

	template<possibly_guarded_handle_of<vk::device> Device, typename F>
	void for_each_image(Device&& device, F&& f) const {
		auto count = get_image_count(device);
		for_feach_image(device, count, forward<F>(f));
	}

}; // handle<swapchain>

#include "acquire_next_image.hpp"
#include "get_images.hpp"