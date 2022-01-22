#pragma once

#include "handle.hpp"
#include "../../pipeline/handle.hpp"
#include "../../pipeline/bind_point.hpp"

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::pipeline>,
		types::are_contain_one_decayed_same_as<vk::pipeline_bind_point>
	>::for_types<Args...>
	void cmd_bind_pipeline(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...);
		vk::pipeline_bind_point bind_point = elements::decayed_same_as<vk::pipeline_bind_point>(args...);
		auto& pipeline = elements::vk::possibly_guarded_handle_of<vk::pipeline>(args...);

		vkCmdBindPipeline(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(VkPipelineBindPoint) bind_point,
			(VkPipeline) vk::get_handle_value(pipeline)
		);
	}

} // vk