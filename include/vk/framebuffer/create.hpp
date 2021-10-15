#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>

#include "create_info.hpp"
#include "../extent.hpp"
#include "../result.hpp"

namespace vk {

	struct device;
	struct framebuffer;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::render_pass&>::equals<1u>,
			types::count_of_type<vk::attachment_count>::remove_reference::equals<1u>,
			types::count_of_type<vk::attachments>::remove_reference::equals<1u>,
			types::count_of_type<vk::extent<3u>>::remove_reference::equals<1u>
		>::for_types_of<Args...>
	)
	vk::framebuffer& create_framebuffer(Args&&... args) {
		vk::framebuffer_create_info ci{
			.render_pass = elements::of_type<vk::render_pass&>::for_elements_of(args...),
			.attachment_count = elements::of_type<vk::attachment_count&>::for_elements_of(args...),
			.attachments = elements::of_type<vk::attachments&>::for_elements_of(args...)
		};

		vk::extent<3u> extent = elements::of_type<vk::extent<3u>&>::for_elements_of(args...);

		ci.width = extent.width();
		ci.height =  extent.height();
		ci.layers = extent.depth();

		vk::framebuffer* framebuffer;
		vk::throw_if_error(
			vkCreateFramebuffer(
				(VkDevice) & elements::of_type<vk::device&>::for_elements_of(args...),
				(VkFramebufferCreateInfo*) &ci,
				nullptr,
				(VkFramebuffer*) &framebuffer
			)
		);

		return *framebuffer;
	}
}