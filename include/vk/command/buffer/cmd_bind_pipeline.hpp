#pragma once

#include "handle.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

#include "vk/pipeline/handle.hpp"
#include "vk/pipeline/bind_point.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_contain_one_possibly_guarded_handle_of<vk::pipeline>,
		types::are_contain_one_decayed<vk::pipeline_bind_point>
	>::for_types<Args...>
	void cmd_bind_pipeline(Args&&... args) {
		auto& command_buffer = elements::possibly_guarded_handle_of<vk::command_buffer>(args...);
		vk::pipeline_bind_point bind_point = elements::decayed<vk::pipeline_bind_point>(args...);
		auto& pipeline = elements::possibly_guarded_handle_of<vk::pipeline>(args...);

		vkCmdBindPipeline(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(VkPipelineBindPoint) bind_point,
			(VkPipeline) vk::get_handle_value(pipeline)
		);
	}

} // vk

template<typename... Args>
auto& handle<vk::command_buffer>::cmd_bind_pipeline(Args&&... args) const {
	vk::cmd_bind_pipeline(*this, forward<Args>(args)...);
	return *this;
}