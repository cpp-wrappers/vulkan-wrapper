#pragma once

#include "../pipeline/stage.hpp"
#include "../access.hpp"
#include "../dependency.hpp"

#include <core/flag_enum.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

namespace vk {

	struct src_subpass { uint32 _; };
	struct dst_subpass { uint32 _; };

	inline constexpr uint32 subpass_external( ~0u );

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
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<vk::src_subpass>,
			types::are_contain_one_decayed<vk::dst_subpass>,
			types::are_contain_one_decayed<vk::src_stages>,
			types::are_contain_one_decayed<vk::dst_stages>,
			types::are_may_contain_one_decayed<vk::src_access>,
			types::are_may_contain_one_decayed<vk::dst_access>
		>::for_types<Args...>
		subpass_dependency(Args... args) {
			src_subpass = elements::decayed<vk::src_subpass>(args...);
			dst_subpass = elements::decayed<vk::dst_subpass>(args...);
			src_stages = elements::decayed<vk::src_stages>(args...);
			dst_stages = elements::decayed<vk::dst_stages>(args...);

			if constexpr (
				types::are_contain_decayed<vk::src_access>::for_types<Args...>
			) { src_access = elements::decayed<vk::src_access>(args...); }

			if constexpr (
				types::are_contain_decayed<vk::dst_access>::for_types<Args...>
			) { dst_access = elements::decayed<vk::dst_access>(args...); }
		} // constructor

	}; // subpass_dependency

} // vk