#pragma once

#include "handle.hpp"
#include "render_pass_begin_info.hpp"

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/meta/types/count_of_decayed_same_as.hpp>

namespace vk {
	
	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_contain_one_decayed_same_as<vk::render_pass_begin_info>
	>::for_types<Args...>
	void cmd_begin_render_pass(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...);
		auto& render_pass_begin_info = elements::decayed_same_as<vk::render_pass_begin_info>(args...);

		vkCmdBeginRenderPass(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(VkRenderPassBeginInfo*) &render_pass_begin_info,
			VK_SUBPASS_CONTENTS_INLINE
		);
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::render_pass>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::framebuffer>,
		types::are_contain_one_decayed_same_as<vk::render_area>,
		types::are_contain_one_range_of_value_type<vk::clear_value>
	>::for_types<Args...>
	void cmd_begin_render_pass(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...);
		auto& render_pass = elements::vk::possibly_guarded_handle_of<vk::render_pass>(args...);
		auto& framebuffer = elements::vk::possibly_guarded_handle_of<vk::framebuffer>(args...);
		vk::render_area render_area = elements::decayed_same_as<vk::render_area>(args...);
		auto& clear_values = elements::range_of_value_type<vk::clear_value>(args...);

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