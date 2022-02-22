#pragma once

#include <core/flag_enum.hpp>
#include <core/c_string.hpp>
#include <core/wrapper/of_integer.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include "vk/headers.hpp"
#include "vk/handle/get_value.hpp"
#include "vk/shader/stage.hpp"
#include "vk/shader/module/handle.hpp"
#include "vk/handle/possibly_guarded_handle_of.hpp"

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
			types::are_contain_one_decayed_same_as<vk::shader_stages>,
			types::are_contain_one_decayed_same_as<vk::entrypoint_name>
		>::for_types<Args...>
		pipeline_shader_stage_create_info(Args&&... args) {
			stages = elements::decayed_same_as<vk::shader_stages>(args...);
			module = vk::get_handle(elements::vk::possibly_guarded_handle_of<vk::shader_module>(args...));
			entrypoint_name = elements::decayed_same_as<vk::entrypoint_name>(args...);
		}

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::shader_module>,
			types::are_contain_one_decayed_same_as<vk::shader_stage>,
			types::are_contain_one_decayed_same_as<vk::entrypoint_name>
		>::for_types<Args...>
		pipeline_shader_stage_create_info(Args&&... args) {
			stages = elements::decayed_same_as<vk::shader_stage>(args...);
			module = vk::get_handle(elements::vk::possibly_guarded_handle_of<vk::shader_module>(args...));
			entrypoint_name = elements::decayed_same_as<vk::entrypoint_name>(args...);
		}
	};

} // vk