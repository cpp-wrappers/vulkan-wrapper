#pragma once

#include "handle.hpp"

#include "../../descriptor/binding.hpp"
#include "../../descriptor/array_element.hpp"
#include "../../descriptor/count.hpp"

namespace vk {

	struct copy_descriptor_set {
		uint32 structure_type = 36;
		const void* next;
		handle<vk::descriptor_set> src_set;
		vk::src_binding src_binding;
		vk::src_array_element src_array_element;
		handle<vk::descriptor_set> dst_set;
		vk::dst_binding dst_binding;
		vk::dst_array_element dst_array_element;
		vk::descriptor_count descriptor_count;
	};

} // vk