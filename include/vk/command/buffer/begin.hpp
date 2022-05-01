#pragma once

#include "handle.hpp"
#include "usage.hpp"
#include "begin_info.hpp"
#include "../../result.hpp"
#include "../../function.hpp"
#include "../../unexpected_handler.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/handle.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR int32 VK_CALL vkBeginCommandBuffer(
	handle<vk::command_buffer>           command_buffer,
	const vk::command_buffer_begin_info* begin_info
);

namespace vk {

	struct command_buffer;

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::command_buffer>>,
		types::are_may_contain_one_decayed<vk::command_buffer_usages>,
		types::are_may_contain_one_decayed<vk::command_buffer_inheritance_info>
	>::for_types<Args...>
	vk::result try_begin_command_buffer(Args&&... args) {
		vk::command_buffer_begin_info bi {};

		if constexpr (
			types::are_contain_decayed<
				vk::command_buffer_usages
			>::for_types<Args...>
		) { bi.usages = elements::decayed<vk::command_buffer_usages>(args...); }

		if constexpr (
			types::are_contain_decayed<
				vk::command_buffer_inheritance_info
			>::for_types<Args...>
		) {
			bi.inheritance_info = {
				elements::decayed<vk::command_buffer_inheritance_info>(args...)
			};
		}

		auto command_buffer {
			elements::decayed<handle<vk::command_buffer>>(args...)
		};

		return { vkBeginCommandBuffer(command_buffer, &bi) };
	}

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::command_buffer>>,
		types::are_contain_one_decayed<vk::command_buffer_usages>,
		types::are_contain_one_decayed<handle<vk::render_pass>>,
		types::are_contain_one_decayed<handle<vk::framebuffer>>,
		types::are_contain_one_decayed<vk::subpass>,
		types::are_may_contain_one_decayed<vk::occlusion_query_enable>,
		types::are_contain_one_decayed<vk::query_control_flags>,
		types::are_contain_one_decayed<vk::query_pipeline_statistic_flags>
	>::for_types<Args...>
	vk::result try_begin_command_buffer(Args&&... args) {
		vk::command_buffer_inheritance_info ii {
			.render_pass = elements::decayed<vk::command_buffer>(args...),
			.subpass = elements::decayed<vk::subpass>(args...),
			.framebuffer = elements::decayed<vk::framebuffer>(args...),
			.query_flags = elements::decayed<vk::query_control_flags>(args...),
			.pipeline_statistics_flags {
				elements::decayed<vk::query_pipeline_statistic_flags>(args...)
			}
		};

		if constexpr (
			types::are_contain_decayed<
				vk::occlusion_query_enable
			>::for_types<Args...>
		) {
			ii.occlusion_query_enable ={
				elements::decayed<vk::occlusion_query_enable>(args...)
			};
		}

		auto usages = elements::decayed<vk::command_buffer_usages>(args...);
		auto command_buffer {
			elements::decayed<handle<vk::command_buffer>>(args...)
		};

		return vk::try_begin_command_buffer(command_buffer, usages, ii);
	}

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::command_buffer>>,
		types::are_contain_decayed<vk::command_buffer_usage>
	>::for_types<Args...>
	vk::result try_begin_command_buffer(Args&&... args) {
		vk::command_buffer_usages usages{};

		elements::for_each_decayed<vk::command_buffer_usage>(args...)(
			[&](vk::command_buffer_usage usage){ usages.set(usage); }
		);

		return vk::try_begin_command_buffer(
			elements::decayed<handle<vk::command_buffer>>(args...),
			usages
		);
	}

	template<typename... Args>
	void begin_command_buffer(Args&&... args) {
		vk::result result {
			vk::try_begin_command_buffer(forward<Args>(args)...)
		};

		if(result.error()) vk::unexpected_handler(result);
	}

} // vk

template<typename... Args>
vk::result handle<vk::command_buffer>::try_begin(Args&&... args) const {
	return vk::try_begin_command_buffer(*this, forward<Args>(args)...);
}

template<typename... Args>
auto& handle<vk::command_buffer>::begin(Args&&... args) const {
	vk::begin_command_buffer(*this, forward<Args>(args)...);
	return *this;
}