#pragma once

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/range/of_value_type_same_as.hpp>

#include "vk/acceleration_structure/handle.hpp"
#include "vk/acceleration_structure/build_geometry_info.hpp"
#include "vk/handle/possibly_guarded_handle_of.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::acceleration_structure>,
		types::are_contain_one_range_of<vk::acceleration_structure_build_geometry_info>
	>::for_types<Args...>
	void cmd_build_acceleration_structure(Args&&... args) {
		
	}

} // vk