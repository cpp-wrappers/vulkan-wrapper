#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>

#include "../../../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../../../object/destroy_or_free.hpp"
#include "../../../device/handle.hpp"

#include "handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::descriptor_set_layout> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::count_of_type<vk::handle<vk::descriptor_set_layout>>::equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
		void operator () (Args&&... args) const {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);
			auto set_layout = elements::of_type<vk::handle<vk::descriptor_set_layout>>::ignore_const::ignore_reference::for_elements_of(args...);

			vkDestroyDescriptorSetLayout(
				(VkDevice) vk::get_handle_value(device),
				(VkDescriptorSetLayout) vk::get_handle_value(set_layout),
				(VkAllocationCallbacks*) nullptr
			);
		}

	};

} // vk