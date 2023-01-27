#pragma once

#include "./type.hpp"

#include "../__buffer/handle.hpp"
#include "../__internal/memory_size.hpp"
#include "../__internal/memory_offset.hpp"
#include "../__internal/device_address.hpp"

#include <enum_flags.hpp>

namespace vk {

	enum class acceleration_structure_create_flag {
		device_address_capture_replay = 0x00000001
	};

	using acceleration_structure_create_flags =
		enum_flags<acceleration_structure_create_flag>;

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