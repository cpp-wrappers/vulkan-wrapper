#pragma once

#include "type.hpp"

#include "../buffer/handle.hpp"
#include "../memory_size.hpp"
#include "../memory_offset.hpp"
#include "../device_address.hpp"

#include <core/flag_enum.hpp>

namespace vk {

	enum class acceleration_structure_create_flag {
		device_address_capture_replay = 0x00000001
	};

	using acceleration_structure_create_flags =
		flag_enum<acceleration_structure_create_flag>;

	struct acceleration_structure_create_info {
		uint32                                  structure_type = 1000150017;
		const void*                             next;
		vk::acceleration_structure_create_flags flags;
		handle<vk::buffer>                      buffer;
		vk::memory_offset                       offset;
		vk::memory_size                         size;
		vk::acceleration_structure_type         type;
		vk::device_address                      device_address;
	};

	namespace as {
		using create_flag = vk::acceleration_structure_create_flag;
		using create_flags = vk::acceleration_structure_create_flags;
		using create_info = vk::acceleration_structure_create_info;
	}

} // vk