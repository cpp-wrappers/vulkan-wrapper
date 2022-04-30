#pragma once

#include "handle.hpp"

#include "../../pipeline/handle.hpp"
#include "../../pipeline/bind_point.hpp"
#include "../../function.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR void VK_CALL vkCmdBindPipeline(
	handle<vk::command_buffer> command_buffer,
	vk::pipeline_bind_point    pipeline_bind_point,
	handle<vk::pipeline>       pipeline
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::command_buffer>>,
		types::are_contain_one_decayed<handle<vk::pipeline>>,
		types::are_contain_one_decayed<vk::pipeline_bind_point>
	>::for_types<Args...>
	void cmd_bind_pipeline(Args&&... args) {
		auto command_buffer {
			elements::decayed<handle<vk::command_buffer>>(args...)
		};

		vk::pipeline_bind_point bind_point {
			elements::decayed<vk::pipeline_bind_point>(args...)
		};

		auto pipeline = elements::decayed<handle<vk::pipeline>>(args...);

		vkCmdBindPipeline(
			command_buffer,
			bind_point,
			pipeline
		);
	}

} // vk

template<typename... Args>
auto& handle<vk::command_buffer>::cmd_bind_pipeline(Args&&... args) const {
	vk::cmd_bind_pipeline(*this, forward<Args>(args)...);
	return *this;
}