#pragma once

#include "../__shader_module/stage.hpp"
#include "../__shader_module/handle.hpp"

#include <enum_flags.hpp>
#include <c_string.hpp>
#include <types.hpp>
#include <tuple.hpp>

#include <unicode/utf8.hpp>

namespace vk {

	enum class shader_stage_create_flag {
		allow_varying_subgroup_size = 0x00000001,
		require_full_subgroups      = 0x00000002
	};

	using shader_stage_create_flags = enum_flags<shader_stage_create_flag>;

	struct entrypoint_name { c_string<utf8::unit> _; };

	struct pipeline_shader_stage_create_info {
		uint32 structure_type = 18;
		const void* next = nullptr;
		shader_stage_create_flags flags{};
		vk::shader_stages stages;
		handle<vk::shader_module>::underlying_type module;
		vk::entrypoint_name entrypoint_name;
		const void* specialization_info = nullptr;

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_same_as<handle<vk::shader_module>>.decayed == 1,
			is_same_as<vk::shader_stages>.decayed == 1,
			is_same_as<vk::entrypoint_name>.decayed == 1
		>
		pipeline_shader_stage_create_info(Args&&... args) :
			stages {
				tuple{ args... }.template
					get<is_same_as<vk::shader_stages>.decayed>()
			},
			module {
				tuple{ args... }.template
					get<is_same_as<handle<vk::shader_module>>.decayed>()
					.underlying()
			},
			entrypoint_name {
				tuple{ args... }.template
					get<is_same_as<vk::entrypoint_name>.decayed>()
			}
		{}

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_same_as<handle<vk::shader_module>>.decayed == 1,
			is_same_as<vk::shader_stage>.decayed == 1,
			is_same_as<vk::entrypoint_name>.decayed == 1
		>
		pipeline_shader_stage_create_info(Args&&... args) :
			stages { vk::shader_stages {
				tuple{ args... }.template
					get<is_same_as<vk::shader_stage>.decayed>()
			}},
			module {
				tuple{ args... }.template
					get<is_same_as<handle<vk::shader_module>>.decayed>()
					.underlying()
			},
			entrypoint_name {
				tuple{ args... }.template
					get<is_same_as<vk::entrypoint_name>.decayed>()
			}
		{}

	}; // pipeline_shader_stage_info

} // vk