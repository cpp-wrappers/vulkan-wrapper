#pragma once

#include "./create_info.hpp"
#include "../__internal/function.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__framebuffer/handle.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct create_framebuffer_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		const vk::framebuffer_create_info* create_info,
		const void* allocator,
		handle<vk::framebuffer>::underlying_type* framebuffer
	)> {
		static constexpr auto name = "vkCreateFramebuffer";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::render_pass>> == 1,
		count_of_range_of_decayed<handle<vk::image_view>> == 1,
		count_of_decayed_same_as<vk::extent<3>> == 1
	>
	vk::expected<handle<vk::framebuffer>>
	try_create_framebuffer(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::render_pass> render_pass = a.template
			get_decayed_same_as<handle<vk::render_pass>>();

		auto& attachments = a.template
			get_range_of_decayed<handle<vk::image_view>>();

		vk::extent<3> extent = a.template get_decayed_same_as<vk::extent<3>>();

		vk::framebuffer_create_info ci {
			.render_pass = (handle<vk::render_pass>::underlying_type)
				render_pass.underlying(),
			.attachment_count = (uint32) attachments.size(),
			.attachments = (const handle<vk::image_view>::underlying_type*)
				attachments.iterator(),
			.width = extent.width(),
			.height = extent.height(),
			.layers = extent.depth()
		};

		handle<vk::framebuffer> framebuffer;

		vk::result result {
			vk::get_device_function<vk::create_framebuffer_function>(
				instance, device
			)(
				device.underlying(),
				&ci,
				nullptr,
				&framebuffer.underlying()
			)
		};

		if(result.error()) return result;

		return framebuffer;
	}

	template<typename... Args>
	handle<vk::framebuffer> create_framebuffer(Args&&... args) {
		vk::expected<handle<vk::framebuffer>> result
			= vk::try_create_framebuffer(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk