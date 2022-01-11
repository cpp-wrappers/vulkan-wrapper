#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>

#include "../../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../device/handle.hpp"
#include "write.hpp"
#include "copy.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::count_of_ranges_of_value_type<vk::write_descriptor_set>::equals<1>,
		types::count_of_ranges_of_value_type<vk::copy_descriptor_set>::equals<1>
	>::for_types_of<Args...>
	void update_descriptor_sets(Args&&... args) {
		auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);
		auto& writes = elements::range_of_value_type<vk::write_descriptor_set>::for_elements_of(args...);
		auto& copies = elements::range_of_value_type<vk::copy_descriptor_set>::for_elements_of(args...);

		vkUpdateDescriptorSets(
			(VkDevice) vk::get_handle_value(device),
			(uint32) writes.size(),
			(VkWriteDescriptorSet*) writes.data(),
			(uint32) copies.size(),
			(VkCopyDescriptorSet*) copies.data()
		);
	}

} // vk