#pragma once

#include "../../shared/extent.hpp"
#include "../../object/create_or_allocate.hpp"
#include "../device/handle.hpp"
#include "handle.hpp"
#include "create_info.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::framebuffer> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::render_pass>,
			types::count_of_ranges_of_value_type<vk::handle<vk::image_view>>::equals<1>,
			types::count_of_type<vk::extent<3>>::equals<1>
		>::for_types_of<Args...>
		vk::expected<vk::handle<vk::framebuffer>>
		operator () (const Args&... args) const {
			auto& attachments = elements::range_of_value_type<vk::handle<vk::image_view>>::for_elements_of(args...);

			auto& render_pass = elements::vk::possibly_guarded_handle_of<vk::render_pass>::for_elements_of(args...);

			vk::framebuffer_create_info ci {
				.render_pass = vk::get_handle(render_pass),
				.attachment_count = (uint32) attachments.size(),
				.attachments = attachments.data()
			};

			vk::extent<3> extent = elements::of_type<const vk::extent<3>&>::for_elements_of(args...);

			ci.width = extent.width();
			ci.height = extent.height();
			ci.layers = extent.depth();

			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);

			VkFramebuffer framebuffer;

			vk::result result {
				(int32) vkCreateFramebuffer(
					(VkDevice) vk::get_handle_value(device),
					(VkFramebufferCreateInfo*) &ci,
					nullptr,
					(VkFramebuffer*) &framebuffer
				)
			};

			if(!result.success()) return result;

			return vk::handle<vk::framebuffer>{ framebuffer };
		}
	};

} // vk