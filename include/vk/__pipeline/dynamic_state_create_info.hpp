#pragma once

#include "../__internal/dynamic_state.hpp"

#include <integer.hpp>
#include <range.hpp>

namespace vk {

	struct pipeline_dynamic_state_create_info {
		uint32               structure_type = 27;
		const void*          next = nullptr;
		uint32               flags = 0;
		uint32               dynamic_state_count = 0;
		const dynamic_state* dynamic_states = nullptr;

		template<range_of_decayed<vk::dynamic_state> DynamicStates>
		pipeline_dynamic_state_create_info(DynamicStates& dynamic_states) :
			dynamic_state_count { (uint32) dynamic_states.size() },
			dynamic_states { dynamic_states.iterator()() }
		{}

	}; // pipeline_dynamic_state_create_info

} // vk