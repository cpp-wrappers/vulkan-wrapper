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
			is_same_as<vk::src_subpass>.decayed == 1,
			is_same_as<vk::dst_subpass>.decayed == 1,
			is_same_as<vk::src_stages>.decayed == 1,
			is_same_as<vk::dst_stages>.decayed == 1,
			is_same_as<vk::src_access>.decayed <= 1,
			is_same_as<vk::dst_access>.decayed <= 1
		>
		subpass_dependency(Args&&... args) {
			tuple a{ args... };
			src_subpass = a.template get<is_same_as<vk::src_subpass>.decayed>();
			dst_subpass = a.template get<is_same_as<vk::dst_subpass>.decayed>();
			src_stages = a.template get<is_same_as<vk::src_stages>.decayed>();
			dst_stages = a.template get<is_same_as<vk::dst_stages>.decayed>();

			if constexpr (
				(is_same_as<vk::src_access>.decayed > 0).for_types<Args...>()
			) { src_access = a.template get<is_same_as<vk::src_access>.decayed>(); }

			if constexpr (
				(is_same_as<vk::dst_access>.decayed > 0).for_types<Args...>()
			) { dst_access = a.template get<is_same_as<vk::dst_access>.decayed>(); }
		} // constructor

	}; // subpass_dependency

} // vk