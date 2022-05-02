#pragma once

#include "handle.hpp"
#include "../../function.hpp"
#include "../../pipeline/layout/handle.hpp"
#include "../../pipeline/push_constant_range.hpp"

extern "C" VK_ATTR void VK_CALL vkCmdPushConstants(
	handle<vk::command_buffer>  command_buffer,
	handle<vk::pipeline_layout> layout,
	vk::shader_stages           stages,
	uint32                      offset,
	uint32                      size,
	const void*                 values
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::command_buffer>>,
		types::are_contain_one_decayed<handle<vk::pipeline_layout>>,
		types::are_contain_one_decayed<vk::push_constant_range>,
		types::are_contain_one_decayed<void*>
	>::for_types<Args...>
	void cmd_push_constants(Args&&... args) {
		auto command_buffer {
			elements::decayed<handle<vk::command_buffer>>(args...)
		};
		auto pipeline_layout {
			elements::decayed<handle<vk::pipeline_layout>>(args...)
		};
		auto range {
			elements::decayed<vk::push_constant_range>(args...)
		};
		auto values {
			elements::decayed<void*>(args...)
		};

		vkCmdPushConstants(
			command_buffer,
			pipeline_layout,
			range.stages,
			range.offset,
			range.size,
			values
		);
	}

} // vk

template<typename... Args>
auto& handle<vk::command_buffer>::cmd_push_constants(Args&&... args) const {
	vk::cmd_push_constants(*this, forward<Args>(args)...);
	return *this;
}