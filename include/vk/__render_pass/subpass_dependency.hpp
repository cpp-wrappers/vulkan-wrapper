#pragma once

#include "../__pipeline/stage.hpp"
#include "../__internal/access.hpp"
#include "../__internal/dependency.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct src_subpass { uint32 _; };
	struct dst_subpass { uint32 _; };

	inline constexpr uint32 subpass_external( ~0u );

	class subpass_dependency {
		vk::src_subpass src_subpass;
		vk::dst_subpass dst_subpass;
		vk::src_stages src_stages;
		vk::dst_stages dst_stages;
		vk::src_access src_access{ vk::access::none };
		vk::dst_access dst_access{ vk::access::none };
		enum_flags<vk::dependency> dependency_flags{};

	public:

		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			count_of_decayed_same_as<vk::src_subpass> == 1,
			count_of_decayed_same_as<vk::dst_subpass> == 1,
			count_of_decayed_same_as<vk::src_stages> == 1,
			count_of_decayed_same_as<vk::dst_stages> == 1,
			count_of_decayed_same_as<vk::src_access> <= 1,
			count_of_decayed_same_as<vk::dst_access> <= 1
		>
		subpass_dependency(Args&&... args) {
			tuple a{ args... };
			src_subpass = a.template get_decayed_same_as<vk::src_subpass>();
			dst_subpass = a.template get_decayed_same_as<vk::dst_subpass>();
			src_stages = a.template get_decayed_same_as<vk::src_stages>();
			dst_stages = a.template get_decayed_same_as<vk::dst_stages>();

			if constexpr (types<Args...>::template
				count_of_decayed_same_as<vk::src_access> > 0
			) { src_access = a.template get_decayed_same_as<vk::src_access>(); }

			if constexpr (types<Args...>::template
				count_of_decayed_same_as<vk::dst_access> > 0
			) { dst_access = a.template get_decayed_same_as<vk::dst_access>(); }
		} // constructor

	}; // subpass_dependency

} // vk