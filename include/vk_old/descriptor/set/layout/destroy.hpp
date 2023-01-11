#pragma once

#include "handle.hpp"

#include "../../../function.hpp"
#include "../../../device/handle.hpp"
#include "../../../destroy_or_free.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR void VK_CALL vkDestroyDescriptorSetLayout(
	handle<vk::device>                device,
	handle<vk::descriptor_set_layout> descriptor_set_layout,
	const void*                       allocator
);

namespace vk {

	template<>
	struct vk::destroy_t<vk::descriptor_set_layout> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<handle<vk::device>>,
			types::are_contain_one_decayed<handle<vk::descriptor_set_layout>>
		>::for_types<Args...>
		void operator () (Args&&... args) const {
			auto device = elements::decayed<handle<vk::device>>(args...);

			auto set_layout {
				elements::decayed<handle<vk::descriptor_set_layout>>(args...)
			};

			vkDestroyDescriptorSetLayout(device, set_layout, (void*) nullptr);
		}

	}; // destroy_t<descriptor_set_layout>

} // vk