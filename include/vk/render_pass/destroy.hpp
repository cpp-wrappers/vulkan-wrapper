#pragma once

#include "../headers.hpp"

namespace vk {

	struct device;
	struct render_pass;

	void inline destroy_render_pass(vk::device& device, vk::render_pass& render_pass) {
		vkDestroyRenderPass(
			(VkDevice) &device,
			(VkRenderPass) &render_pass,
			nullptr
		);
	}
}