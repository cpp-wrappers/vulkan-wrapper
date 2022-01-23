#pragma once

#include "handle.hpp"
#include "create_info.hpp"
#include "../device/handle.hpp"
#include "../create_or_allocate.hpp"
#include "../extent.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::framebuffer> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::render_pass>,
			types::are_contain_one_range_of_value_type<vk::handle<vk::image_view>>,
			types::are_contain_one_decayed_same_as<vk::extent<3>>
		>::for_types<Args...>
		vk::expected<vk::handle<vk::framebuffer>>
		operator () (const Args&... args) const {
			auto& attachments = elements::range_of_value_type<vk::handle<vk::image_view>>(args...);

			auto& render_pass = elements::vk::possibly_guarded_handle_of<vk::render_pass>(args...);

			vk::framebuffer_create_info ci {
				.render_pass = vk::get_handle(render_pass),
				.attachment_count = (uint32) attachments.size(),
				.attachments = attachments.data()
			};

			vk::extent<3> extent = elements::decayed_same_as<vk::extent<3>>(args...);

			ci.width = extent.width();
			ci.height = extent.height();
			ci.layers = extent.depth();

			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);

			vk::handle<vk::framebuffer> framebuffer;

			vk::result result {
				(int32) vkCreateFramebuffer(
					(VkDevice) vk::get_handle_value(device),
					(VkFramebufferCreateInfo*) &ci,
					(VkAllocationCallbacks*) nullptr,
					(VkFramebuffer*) &framebuffer
				)
			};

			if(result.error()) return result;

			return framebuffer;
		}
	};

} // vk