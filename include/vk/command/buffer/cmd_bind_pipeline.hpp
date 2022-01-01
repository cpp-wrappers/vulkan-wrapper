#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>

#include "../../pipeline/graphics/handle.hpp"
#include "../../pipeline/bind_point.hpp"
#include "handle.hpp"

namespace vk {

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::contain_one<vk::command_buffer>,
			types::count_of_type<vk::pipeline_bind_point>::equals<1>::ignore_const::ignore_reference,
			types::vk::contain_one<vk::pipeline>
		>::for_types_of<Args...>
	)
	void cmd_bind_pipeline(Args&&... args) {
		auto& command_buffer = elements::vk::of_type<vk::command_buffer>::for_elements_of(args...);
		vk::pipeline_bind_point bind_point = elements::of_type<vk::pipeline_bind_point>::ignore_const::ignore_reference::for_elements_of(args...);
		auto& pipeline = elements::vk::of_type<vk::pipeline>::for_elements_of(args...);

		vkCmdBindPipeline(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(VkPipelineBindPoint) bind_point,
			(VkPipeline) vk::get_handle_value(pipeline)
		);
	}

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::vk::contain_one<vk::command_buffer>,
			types::vk::contain_one<vk::graphics_pipeline>
		>::for_types_of<Args...>
	)
	void cmd_bind_pipeline(Args&&... args) {
		auto& command_buffer = elements::vk::of_type<vk::command_buffer>::for_elements_of(args...);
		auto& pipeline = elements::vk::of_type<vk::graphics_pipeline>::for_elements_of(args...);

		vkCmdBindPipeline(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(VkPipelineBindPoint) VK_PIPELINE_BIND_POINT_GRAPHICS,
			(VkPipeline) vk::get_handle_value(pipeline)
		);
	}

} // vk