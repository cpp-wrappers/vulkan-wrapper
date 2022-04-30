#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include "../device/handle.hpp"
#include "../create_or_allocate.hpp"
#include "../extent.hpp"
#include "../function.hpp"

extern "C" VK_ATTR int32 VK_CALL vkCreateFramebuffer(
	handle<vk::device>                 device,
	const vk::framebuffer_create_info* create_info,
	const void*                        allocator,
	handle<vk::framebuffer>*           framebuffer
);

namespace vk {

	template<>
	struct vk::create_t<vk::framebuffer> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<handle<vk::device>>,
			types::are_contain_one_decayed<handle<vk::render_pass>>,
			types::are_contain_range_of<handle<vk::image_view>>,
			types::are_contain_one_decayed<vk::extent<3>>
		>::for_types<Args...>
		vk::expected<handle<vk::framebuffer>>
		operator () (const Args&... args) const {
			auto& attachments = elements::range_of<
				handle<vk::image_view>
			>(args...);

			auto render_pass {
				elements::decayed<handle<vk::render_pass>>(args...)
			};

			vk::framebuffer_create_info ci {
				.render_pass = render_pass,
				.attachment_count = (uint32) attachments.size(),
				.attachments = attachments.data()
			};

			vk::extent<3> extent = elements::decayed<vk::extent<3>>(args...);

			ci.width = extent.width();
			ci.height = extent.height();
			ci.layers = extent.depth();

			auto device {
				elements::decayed<handle<vk::device>>(args...)
			};

			handle<vk::framebuffer> framebuffer;

			vk::result result {
				vkCreateFramebuffer(
					device,
					&ci,
					nullptr,
					&framebuffer
				)
			};

			if(result.error()) return result;

			return framebuffer;
		}

	}; // create_t<framebuffer>

} // vk