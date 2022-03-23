#pragma once

#include "handle.hpp"
#include "render_pass_begin_info.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

namespace vk {
	
	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_contain_one_decayed<vk::render_pass_begin_info>
	>::for_types<Args...>
	void cmd_begin_render_pass(Args&&... args) {
		auto& command_buffer = elements::possibly_guarded_handle_of<vk::command_buffer>(args...);
		auto& render_pass_begin_info = elements::decayed<vk::render_pass_begin_info>(args...);

		vkCmdBeginRenderPass(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(VkRenderPassBeginInfo*) &render_pass_begin_info,
			VK_SUBPASS_CONTENTS_INLINE
		);
	}

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_contain_one_possibly_guarded_handle_of<vk::render_pass>,
		types::are_contain_one_possibly_guarded_handle_of<vk::framebuffer>,
		types::are_contain_one_decayed<vk::render_area>,
		types::are_contain_range_of<vk::clear_value>
	>::for_types<Args...>
	void cmd_begin_render_pass(Args&&... args) {
		auto& command_buffer = elements::possibly_guarded_handle_of<vk::command_buffer>(args...);
		auto& render_pass = elements::possibly_guarded_handle_of<vk::render_pass>(args...);
		auto& framebuffer = elements::possibly_guarded_handle_of<vk::framebuffer>(args...);
		vk::render_area render_area = elements::decayed<vk::render_area>(args...);
		auto& clear_values = elements::range_of<vk::clear_value>(args...);

		return vk::cmd_begin_render_pass(
			command_buffer,
			vk::render_pass_begin_info {
				.render_pass = render_pass,
				.framebuffer = framebuffer,
				.render_area = render_area,
				.clear_value_count = (uint32) clear_values.size(),
				.clear_values = clear_values.data()
			}
		);
	}

} // vk

template<typename... Args>
auto& handle<vk::command_buffer>::cmd_begin_render_pass(Args&&... args) const {
	vk::cmd_begin_render_pass(*this, forward<Args>(args)...);
	return *this;
}