#pragma once

#include <core/integer.hpp>
#include <core/flag_enum.hpp>
#include <core/null_terminated_string_view.hpp>

#include "../headers.hpp"
#include "../shader/stage.hpp"

namespace vk {

	struct shader_module;

	enum class shader_stage_create_flag {
		allow_varying_subgroup_size = VK_PIPELINE_SHADER_STAGE_CREATE_ALLOW_VARYING_SUBGROUP_SIZE_BIT_EXT,
		require_full_subgroups = VK_PIPELINE_SHADER_STAGE_CREATE_REQUIRE_FULL_SUBGROUPS_BIT_EXT
	};

	struct pipeline_shader_stage_create_info {
		uint32 type = (primitive::uint32) VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		const void* next{};
		flag_enum<vk::shader_stage_create_flag> flags;
		flag_enum<vk::shader_stage> stage;
		vk::shader_module& module;
		null_terminated_string_view<size_is::undefined> entry_point_name;
		const void* specialization_info{};
	};
}