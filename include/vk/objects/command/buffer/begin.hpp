#pragma once

#include <core/elements/for_each_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/types/are_contain_type.hpp>

#include "../../../elements/possibly_guarded_handle_of.hpp"
#include "../../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../../object/handle/get_value.hpp"
#include "../../../shared/result.hpp"
#include "begin_info.hpp"

namespace vk {

	struct command_buffer;

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::count_of_type<vk::command_buffer_usages>::equals<1>,
		types::count_of_type<vk::command_buffer_inheritance_info>::less_or_equals<1>
	>::for_types_of<decay<Args>...>
	vk::result try_begin_command_buffer(Args&&... args) {
		vk::command_buffer_begin_info bi {
			.usages = elements::of_type<vk::command_buffer_usages>(args...)
		};

		if constexpr(types::are_contain_type<vk::command_buffer_inheritance_info>::for_types_of<decay<Args>...>) {
			bi.inheritance_info = elements::of_type<vk::command_buffer_inheritance_info>(args...);
		}

		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...);

		return {
			(int32) vkBeginCommandBuffer(
				(VkCommandBuffer) vk::get_handle_value(command_buffer),
				(VkCommandBufferBeginInfo*) &bi
			)
		};
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::count_of_type<vk::command_buffer_usages>::equals<1>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::render_pass>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::framebuffer>,
		types::count_of_type<vk::subpass>::equals<1>,
		types::count_of_type<vk::occlusion_query_enable>::less_or_equals<1>,
		types::count_of_type<vk::query_control_flags>::equals<1>,
		types::count_of_type<vk::query_pipeline_statistic_flags>::equals<1>
	>::for_types_of<decay<Args>...>
	vk::result try_begin_command_buffer(Args&&... args) {
		vk::command_buffer_inheritance_info inheritance_info {
			.render_pass = elements::of_type<vk::command_buffer>(args...),
			.subpass = elements::of_type<vk::subpass>(args...),
			.framebuffer = elements::of_type<vk::framebuffer>(args...),
			.occlusion_query_enable = elements::of_type<vk::occlusion_query_enable>(args...),
			.query_flags = elements::of_type<vk::query_control_flags>(args...),
			.pipeline_statistics_flags = elements::of_type<vk::query_pipeline_statistic_flags>(args...)
		};

		auto usages = elements::of_type<vk::command_buffer_usages>(args...);
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...);

		return vk::try_begin_command_buffer(command_buffer, usages, inheritance_info);
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::count_of_type<vk::command_buffer_usage>::greater_or_equals<1>
	>::for_types_of<decay<Args>...>
	vk::result try_begin_command_buffer(Args&&... args) {
		vk::command_buffer_usages usages;

		elements::for_each_of_type<vk::command_buffer_usage>::function {
			[&](vk::command_buffer_usage usage){ usages.set(usage); }
		}.for_elements_of(args...);

		return vk::try_begin_command_buffer(
			elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...),
			usages
		);
	}

	template<typename... Args>
	void begin_command_buffer(Args&&... args) {
		vk::result result = vk::try_begin_command_buffer(forward<Args>(args)...);
		if(result.error()) default_unexpected_handler(result);
	}

} // vk