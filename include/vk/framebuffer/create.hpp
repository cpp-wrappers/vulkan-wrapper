#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/elements/one_of.hpp>

#include "handle.hpp"
#include "create_info.hpp"
#include "../shared/extent.hpp"
#include "../shared/result.hpp"
#include "../device/handle.hpp"
#include "../shared/guarded.hpp"

namespace vk {

	struct device;
	struct framebuffer;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::contain_one<vk::device>,
			types::vk::contain_one<vk::render_pass>,
			types::count_of_ranges_of_value_type<vk::image_view>::equals<1>,
			types::count_of_type<vk::extent<3>>::equals<1>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::framebuffer>
	try_create_framebuffer(const Args&... args) {
		auto& attachments = elements::range_of_value_type<vk::image_view>::for_elements_of(args...);

		auto& render_pass = elements::vk::of_type<vk::render_pass>::for_elements_of(args...);

		vk::framebuffer_create_info ci {
			.render_pass = vk::get_handle<vk::render_pass>(render_pass),
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
				(VkDevice) vk::get_raw_handle<vk::device>(device),
				(VkFramebufferCreateInfo*) &ci,
				nullptr,
				(VkFramebuffer*) &framebuffer
			)
		};

		if(!result.success()) return result;

		return vk::framebuffer{ framebuffer };
	}

	template<typename... Args>
	vk::framebuffer create_framebuffer(Args&&... args) {
		auto result = try_create_framebuffer(forward<Args>(args)...);
		if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
		return result.template get<vk::framebuffer>();
	}
}