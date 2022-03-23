#pragma once

#include "handle.hpp"

#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

#include "vk/device/handle.hpp"
#include "vk/destroy_or_free.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::descriptor_set_layout> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_contain_one_decayed<handle<vk::descriptor_set_layout>>
		>::for_types<Args...>
		void operator () (Args&&... args) const {
			auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);
			auto set_layout = elements::decayed<handle<vk::descriptor_set_layout>>(args...);

			vkDestroyDescriptorSetLayout(
				(VkDevice) vk::get_handle_value(device),
				(VkDescriptorSetLayout) vk::get_handle_value(set_layout),
				(VkAllocationCallbacks*) nullptr
			);
		}

	};

} // vk