#pragma once

#include "../features.hpp"

namespace vk {

	struct physical_device_acceleration_structure_features :
		vk::physical_device_features_marker
	{
		uint32 structure_type = 1000150013;
		const void* next;
		uint32 acceleration_structure;
		uint32 acceleration_structure_capture_replay;
		uint32 acceleration_structure_indirect_build;
		uint32 acceleration_structure_host_commands;
		uint32 descriptor_binding_acceleration_structure_update_after_bind;
	};

} // vk