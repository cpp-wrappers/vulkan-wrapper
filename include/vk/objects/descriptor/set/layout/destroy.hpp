#pragma once

#include "handle.hpp"
#include "../../../device/handle.hpp"
#include "../../../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../../../object/destroy_or_free.hpp"

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/meta/types/are_contain_decayed_same_as.hpp>
#include <core/meta/elements/decayed_same_as.hpp>

namespace vk {

	template<>
	struct vk::destroy_t<vk::descriptor_set_layout> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_contain_one_decayed_same_as<vk::handle<vk::descriptor_set_layout>>
		>::for_types<Args...>
		void operator () (Args&&... args) const {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);
			auto set_layout = elements::decayed_same_as<vk::handle<vk::descriptor_set_layout>>(args...);

			vkDestroyDescriptorSetLayout(
				(VkDevice) vk::get_handle_value(device),
				(VkDescriptorSetLayout) vk::get_handle_value(set_layout),
				(VkAllocationCallbacks*) nullptr
			);
		}

	};

} // vk