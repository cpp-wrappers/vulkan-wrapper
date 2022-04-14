#pragma once

#include "handle.hpp"

#include "../../function.hpp"
#include "../../device/handle.hpp"
#include "../../destroy_or_free.hpp"

extern "C" VK_ATTR void VK_CALL vkDestroyImageView(
	handle<vk::device> device,
	handle<vk::image_view> image_view,
	const void* allocator
);

namespace vk {

	template<>
	struct vk::destroy_t<vk::image_view> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_contain_one_decayed<handle<vk::image_view>>
		>::for_types<Args...>
		void operator () (Args&&... args) const {
			auto& device = elements::possibly_guarded_handle_of<
				vk::device
			>(args...);

			auto image_view = elements::decayed<
				handle<vk::image_view>
			>(args...);

			vkDestroyImageView(
				vk::get_handle(device),
				image_view,
				(void*) nullptr
			);

		} // operator ()

	}; // destroy_t<image_view>

} // vk