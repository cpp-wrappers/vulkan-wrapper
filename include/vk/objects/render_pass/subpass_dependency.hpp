#pragma once

#include <core/flag_enum.hpp>
#include <core/integer.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/wrapper/of_integer.hpp>

#include "../../shared/access.hpp"
#include "../../shared/dependency.hpp"
#include "../pipeline/stage.hpp"

namespace vk {

	struct src_subpass : wrapper::of_integer<uint32> {};
	struct dst_subpass : wrapper::of_integer<uint32> {};

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
		requires types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::src_subpass>::equals<1>,
			types::count_of_type<vk::dst_subpass>::equals<1>,
			types::count_of_type<vk::src_stages>::equals<1>,
			types::count_of_type<vk::dst_stages>::equals<1>,
			types::count_of_type<vk::src_access>::less_or_equals<1>,
			types::count_of_type<vk::dst_access>::less_or_equals<1>
		>::for_types_of<Args...>
		subpass_dependency(Args... args) {
			src_subpass = elements::of_type<vk::src_subpass>(args...);
			dst_subpass = elements::of_type<vk::dst_subpass>(args...);
			src_stages = elements::of_type<vk::src_stages>(args...);
			dst_stages = elements::of_type<vk::dst_stages>(args...);

			if constexpr(types::count_of_type<vk::src_access>::for_types_of<Args...> == 1)
				src_access = elements::of_type<vk::src_access>(args...);

			if constexpr(types::count_of_type<vk::dst_access>::for_types_of<Args...> == 1)
				dst_access = elements::of_type<vk::dst_access>(args...);
		}
	};

} // vk

static_assert(sizeof(vk::subpass_dependency) == sizeof(VkSubpassDependency));