#pragma once

#include <core/integer.hpp>
#include <core/flag_enum.hpp>
#include <core/c_string.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>

#include "../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../elements/possibly_guarded_handle_of.hpp"
#include "../../shared/headers.hpp"
#include "../../object/handle/get_value.hpp"
#include "../shader/stage.hpp"
#include "../shader/module/handle.hpp"

namespace vk {

	enum class shader_stage_create_flag {
		allow_varying_subgroup_size = VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT,
		require_full_subgroups = VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT
	};

	struct entrypoint_name : wrapper::of<c_string> {};

	struct pipeline_shader_stage_create_info {
		const uint32 type = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		const void* const next = nullptr;
		flag_enum<vk::shader_stage_create_flag> flags{};
		vk::shader_stages stages;
		vk::handle<vk::shader_module> module;
		vk::entrypoint_name entrypoint_name;
		const void* specialization_info = nullptr;

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::shader_module>,
			types::count_of_type<vk::shader_stages>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::entrypoint_name>::equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
		pipeline_shader_stage_create_info(Args&&... args) {
			stages = elements::of_type<vk::shader_stages>::ignore_const::ignore_reference::for_elements_of(args...);
			module = vk::get_handle(elements::vk::possibly_guarded_handle_of<vk::shader_module>::for_elements_of(args...));
			entrypoint_name = elements::of_type<vk::entrypoint_name>::ignore_const::ignore_reference::for_elements_of(args...);
		}

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::shader_module>,
			types::count_of_type<vk::shader_stage>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::entrypoint_name>::equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
		pipeline_shader_stage_create_info(Args&&... args) {
			stages = elements::of_type<vk::shader_stage>::ignore_const::ignore_reference::for_elements_of(args...);
			module = vk::get_handle(elements::vk::possibly_guarded_handle_of<vk::shader_module>::for_elements_of(args...));
			entrypoint_name = elements::of_type<vk::entrypoint_name>::ignore_const::ignore_reference::for_elements_of(args...);
		}
	};

} // vk