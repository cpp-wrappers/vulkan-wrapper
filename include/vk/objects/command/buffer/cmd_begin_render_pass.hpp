#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>

#include "handle.hpp"
#include "render_pass_begin_info.hpp"

namespace vk {
	
	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
			types::count_of_type<vk::render_pass_begin_info>::equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
	)
	void cmd_begin_render_pass(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>::for_elements_of(args...);
		auto& render_pass_begin_info = elements::of_type<vk::render_pass_begin_info>::ignore_const::ignore_reference::for_elements_of(args...);

		vkCmdBeginRenderPass(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(VkRenderPassBeginInfo*) &render_pass_begin_info,
			VK_SUBPASS_CONTENTS_INLINE
		);
	}

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::render_pass>,
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::framebuffer>,
			types::count_of_type<vk::render_area>::equals<1>::ignore_const::ignore_reference,
			types::count_of_ranges_of_value_type<vk::clear_value>::equals<1>
		>::for_types_of<Args...>
	)
	void cmd_begin_render_pass(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>::for_elements_of(args...);
		auto& render_pass = elements::vk::possibly_guarded_handle_of<vk::render_pass>::for_elements_of(args...);
		auto& framebuffer = elements::vk::possibly_guarded_handle_of<vk::framebuffer>::for_elements_of(args...);
		vk::render_area render_area = elements::of_type<vk::render_area>::ignore_const::ignore_reference::for_elements_of(args...);
		auto& clear_values = elements::range_of_value_type<vk::clear_value>::for_elements_of(args...);

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
}