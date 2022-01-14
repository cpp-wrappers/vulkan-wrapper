#pragma once

#include <core/elements/for_each_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/types/are_contain_type.hpp>

#include "../../../elements/possibly_guarded_handle_of.hpp"
#include "../../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../../object/handle/get_value.hpp"
#include "handle.hpp"
#include "begin_info.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::count_of_type<vk::command_buffer_usages>::equals<1>::ignore_const::ignore_reference,
		types::count_of_type<vk::command_buffer_inheritance_info>::less_or_equals<1>::ignore_const::ignore_reference
	>::for_types_of<Args...>
	vk::result try_begin_command_buffer(Args&&... args) {
		vk::command_buffer_begin_info bi {
			.usages = elements::of_type<vk::command_buffer_usages>::ignore_const::ignore_reference::for_elements_of(args...)
		};

		if constexpr(types::are_contain_type<vk::command_buffer_inheritance_info>::ignore_const::ignore_reference::for_types_of<Args...>) {
			bi.inheritance_info = elements::of_type<vk::command_buffer_inheritance_info>::ignore_const::ignore_reference::for_elements_of(args...);
		}

		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>::for_elements_of(args...);

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
		types::count_of_type<vk::command_buffer_usages>::equals<1>::ignore_const::ignore_reference,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::render_pass>,
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::framebuffer>,
		types::count_of_type<vk::subpass>::equals<1>::ignore_const::ignore_reference,
		types::count_of_type<vk::occlusion_query_enable>::less_or_equals<1>::ignore_const::ignore_reference,
		types::count_of_type<vk::query_control_flags>::equals<1>::ignore_const::ignore_reference,
		types::count_of_type<vk::query_pipeline_statistic_flags>::equals<1>::ignore_const::ignore_reference
	>::for_types_of<Args...>
	vk::result try_begin_command_buffer(Args&&... args) {
		vk::command_buffer_inheritance_info inheritance_info {
			.render_pass = elements::of_type<vk::command_buffer>::for_elements_of<Args...>(args...),
			.subpass = elements::of_type<vk::subpass>::for_elements_of<Args...>(args...),
			.framebuffer = elements::of_type<vk::framebuffer>::for_elements_of<Args...>(args...),
			.occlusion_query_enable = elements::of_type<vk::occlusion_query_enable>::ignore_const::ignore_reference::for_elements_of<Args...>(args...),
			.query_flags = elements::of_type<vk::query_control_flags>::ignore_const::ignore_reference::for_elements_of<Args...>(args...),
			.pipeline_statistics_flags = elements::of_type<vk::query_pipeline_statistic_flags>::ignore_const::ignore_reference::for_elements_of<Args...>(args...)
		};

		auto usages = elements::of_type<vk::command_buffer_usages>::ignore_const::ignore_reference::for_elements_of(args...);
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>::for_elements_of(args...);

		return vk::try_begin_command_buffer(command_buffer, usages, inheritance_info);
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::count_of_type<vk::command_buffer_usage>::greater_or_equals<1>::ignore_const::ignore_reference
	>::for_types_of<Args...>
	vk::result try_begin_command_buffer(Args&&... args) {
		vk::command_buffer_usages usages;

		elements::for_each_of_type<vk::command_buffer_usage>::ignore_const::ignore_reference::function {
			[&](vk::command_buffer_usage usage){ usages.set(usage); }
		}.for_elements_of(args...);

		return vk::try_begin_command_buffer(
			elements::vk::possibly_guarded_handle_of<vk::command_buffer>::for_elements_of(args...),
			usages
		);
	}

	template<typename... Args>
	void begin_command_buffer(Args&&... args) {
		vk::result result = vk::try_begin_command_buffer(forward<Args>(args)...);
		if(!result.success()) throw result;
	}
}