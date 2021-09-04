#pragma once

#include <cstdint>

#include <core/flag_enum.hpp>
#include <core/named.hpp>
#include <core/tuple.hpp>

#include "pipeline_stage.hpp"
#include "access.hpp"
#include "dependency.hpp"

namespace vk {

struct src_subpass : named<std::uint32_t> {};
struct dst_subpass : named<std::uint32_t> {};

struct src_stages : named<flag_enum<vk::pipeline_stage>> {};
struct dst_stages : named<flag_enum<vk::pipeline_stage>> {};

struct src_access : named<flag_enum<vk::access>> {};
struct dst_access : named<flag_enum<vk::access>> {};

class subpass_dependency {
	vk::src_subpass src_subpass;
	vk::dst_subpass dst_subpass;
	vk::src_stages src_stages;
	vk::dst_stages dst_stages;
	vk::src_access src_access;
	vk::dst_access dst_access;
	flag_enum<vk::dependency> dependency_flags;
public:

	template<typename... Args>
	requires(
		types::of<Args...>::template count_of_type<vk::src_subpass> == 1 &&
		types::of<Args...>::template count_of_type<vk::dst_subpass> == 1 &&
		types::of<Args...>::template count_of_type<vk::src_stages> == 1 &&
		types::of<Args...>::template count_of_type<vk::dst_stages> == 1 &&
		types::of<Args...>::template count_of_type<vk::src_access> == 1 &&
		types::of<Args...>::template count_of_type<vk::dst_access> == 1 &&
		types::of<Args...>::template erase_types<
			vk::src_subpass, vk::dst_subpass, vk::src_stages,
			vk::dst_stages, vk::src_access, vk::dst_access,
			vk::dependency
		>::empty
	)
	subpass_dependency(Args... args) {
		tuple{ args... }
			.get([&](vk::src_subpass s) { src_subpass = s; })
			.get([&](vk::dst_subpass d) { dst_subpass = d; })
			.get([&](vk::src_stages s) { src_stages = s; })
			.get([&](vk::dst_stages d) { dst_stages = d; })
			.get([&](vk::src_access s) { src_access = s; })
			.get([&](vk::dst_access d) { dst_access = d; })
			.get([&](vk::dependency f) { dependency_flags.set(f); })
		;
	}
};

}

static_assert(sizeof(vk::subpass_dependency) == sizeof(VkSubpassDependency));