#pragma once

#include "image_index.hpp"

#include "../semaphore/handle.hpp"
#include "../fence/handle.hpp"
#include "../timeout.hpp"
#include "../result.hpp"
#include "../count.hpp"
#include "../image/handle.hpp"
#include "../create_or_allocate.hpp"

#include <core/span.hpp>
#include <core/forward.hpp>
#include <core/exchange.hpp>
#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/decayed_same_as.hpp>

namespace vk {

	struct semaphore;
	struct fence;
	struct image;
	struct device;
	struct swapchain;

	template<>
	inline constexpr bool is_creatable<vk::swapchain> = true;

} // vk

template<>
struct handle<vk::swapchain> : vk::handle_base<vk::non_dispatchable> {

	template<typename... Args>
	vk::expected<vk::image_index> try_acquire_next_image(Args&&...) const;

	template<typename... Args>
	vk::count get_images(Args&&...) const;

	vk::count inline get_image_count(handle<vk::device> device) const;

	decltype(auto)
	view_images(handle<vk::device> device, vk::count count, auto&& f) const;

	template<typename F>
	decltype(auto)
	view_images(handle<vk::device> device, F&& f) const;

	void for_each_image(
		handle<vk::device> device, vk::count count, auto&& f
	) const;

	template<typename F>
	void for_each_image(handle<vk::device> device, F&& f) const;

}; // handle<swapchain>

#include "acquire_next_image.hpp"
#include "get_images.hpp"