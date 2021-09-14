#pragma once

#include "../headers.hpp"
#include "descriptor_type.hpp"
#include <core/named.hpp>
#include <core/flag_enum.hpp>
#include <core/tuple.hpp>
#include "shader_stage.hpp"

namespace vk {

struct descriptor_binding : named<uint32_t> {};
struct descriptor_count : named<uint32_t> {};

struct descriptor_set_layout_binding {
	vk::descriptor_binding m_binding;
	vk::descriptor_type m_descriptor_type;
	u::bitmask_from_enum<vk::shader_stage> m_stage_flags;
	const void* m_immutable_samplers;

	template<typename... Ps>
	descriptor_set_layout_binding(Ps&&... params) {
		u::params<Ps&...>{ params...}
			.template handle<u::required>([&](descriptor_binding b){ m_binding = b; })
			.template handle<u::required>([&](descriptor_type t){ m_descriptor_type = t; })
			.template handle<u::several>([&](vk::shader_stage s){ m_stage_flags.set(s); })
			// TODO samplers
			.check_for_emptiness();
	}
}; // descriptor_set_layout_binding

} // vk

static_assert(sizeof(vk::descriptor_set_layout_binding) == sizeof(VkDescriptorSetLayoutBinding));