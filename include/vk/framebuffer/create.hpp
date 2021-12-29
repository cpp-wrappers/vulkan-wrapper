#pragma once

#include "handle.hpp"
#include "create_info.hpp"
#include "../shared/extent.hpp"
#include "../device/handle.hpp"
#include "../shared/create.hpp"

namespace vk {

	struct device;
	struct framebuffer;

	template<>
	struct vk::try_create_t<vk::framebuffer> {

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::vk::contain_one<vk::device>,
				types::vk::contain_one<vk::render_pass>,
				types::count_of_ranges_of_value_type<vk::handle<vk::image_view>>::equals<1>,
				types::count_of_type<vk::extent<3>>::equals<1>
			>::for_types_of<Args...>
		)
		elements::one_of<vk::result, vk::handle<vk::framebuffer>>
		operator () (const Args&... args) const {
			auto& attachments = elements::range_of_value_type<vk::handle<vk::image_view>>::for_elements_of(args...);

			auto& render_pass = elements::vk::of_type<vk::render_pass>::for_elements_of(args...);

			vk::framebuffer_create_info ci {
				.render_pass = vk::get_handle(render_pass),
				.attachment_count = (uint32) attachments.size(),
				.attachments = attachments.data()
			};

			vk::extent<3> extent = elements::of_type<const vk::extent<3>&>::for_elements_of(args...);

			ci.width = extent.width();
			ci.height = extent.height();
			ci.layers = extent.depth();

			auto& device = elements::vk::of_type<vk::device>::for_elements_of(args...);

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
}