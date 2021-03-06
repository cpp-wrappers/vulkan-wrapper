#pragma once

#include "../dynamic_state.hpp"

#include <core/integer.hpp>
#include <core/range_of_value_type_same_as.hpp>

namespace vk {

	struct pipeline_dynamic_state_create_info {
		uint32               structure_type = 27;
		const void*          next = nullptr;
		uint32               flags = 0;
		uint32               dynamic_state_count = 0;
		const dynamic_state* dynamic_states = nullptr;

		template<range_of<vk::dynamic_state> DynamicStates>
		pipeline_dynamic_state_create_info(DynamicStates& dynamic_states) :
			dynamic_state_count { (uint32) dynamic_states.size() },
			dynamic_states { dynamic_states.data() }
		{}

	}; // pipeline_dynamic_state_create_info

} // vk