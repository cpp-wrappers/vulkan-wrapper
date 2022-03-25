#pragma once

#include "../handle/get_value.hpp"
#include "../shader/stage.hpp"
#include "../shader/module/handle.hpp"

#include <core/flag_enum.hpp>
#include <core/c_string.hpp>
#include <core/wrapper/of_integer.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/handle/possibly_guarded_of.hpp>

namespace vk {

	enum class shader_stage_create_flag {
		allow_varying_subgroup_size = 0x00000001,
		require_full_subgroups      = 0x00000002
	};

	using shader_stage_create_flags = flag_enum<shader_stage_create_flag>;

	struct entrypoint_name : wrapper::of<c_string> {};

	struct pipeline_shader_stage_create_info {
		uint32 structure_type = 18;
		const void* next = nullptr;
		shader_stage_create_flags flags{};
		vk::shader_stages stages;
		handle<vk::shader_module> module;
		vk::entrypoint_name entrypoint_name;
		const void* specialization_info = nullptr;

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_possibly_guarded_handle_of<
				vk::shader_module
			>,
			types::are_contain_one_decayed<vk::shader_stage>,
			types::are_contain_one_decayed<vk::entrypoint_name>
		>::for_types<Args...>
		pipeline_shader_stage_create_info(Args&&... args) {
			stages = elements::decayed<vk::shader_stage>(args...);

			auto& shader_module {
				elements::possibly_guarded_handle_of<vk::shader_module>(args...)
			};
			module = vk::get_handle(shader_module);
			entrypoint_name = elements::decayed<vk::entrypoint_name>(args...);

		} // constructor

	}; // pipeline_shader_stage_info

} // vk