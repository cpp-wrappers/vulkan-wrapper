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
		types::count_of_ranges_of_value_type<vk::write_descriptor_set>::less_or_equals<1>,
		types::count_of_ranges_of_value_type<vk::copy_descriptor_set>::less_or_equals<1>
	>::for_types_of<decay<Args>...>
	void update_descriptor_sets(Args&&... args) {
		auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);

		uint32 write_count{};
		const vk::write_descriptor_set* writes;

		if constexpr(types::are_contain_range_of_value_type<vk::write_descriptor_set>::for_types_of<decay<Args>...>) {
			auto& writes0 = elements::range_of_value_type<vk::write_descriptor_set>(args...);
			write_count = (uint32) writes0.size();
			writes = writes0.data();
		}

		uint32 copy_count{};
		const vk::copy_descriptor_set* copies;

		if constexpr(types::are_contain_range_of_value_type<vk::copy_descriptor_set>::for_types_of<decay<Args>...>) {
			auto& copies0 = elements::range_of_value_type<vk::copy_descriptor_set>(args...);
			copy_count = (uint32) copies0.size();
			copies = copies0.data();
		}

		vkUpdateDescriptorSets(
			(VkDevice) vk::get_handle_value(device),
			write_count,
			(VkWriteDescriptorSet*) writes,
			copy_count,
			(VkCopyDescriptorSet*) copies
		);
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_type<vk::write_descriptor_set>
	>::for_types_of<decay<Args>...>
	void update_descriptor_set(Args&&... args) {
		return vk::update_descriptor_sets(
			elements::vk::possibly_guarded_handle_of<vk::device>(args...),
			array{
				elements::of_type<vk::write_descriptor_set>(args...)
			}
		);
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_type<vk::copy_descriptor_set>
	>::for_types_of<decay<Args>...>
	void update_descriptor_set(Args&&... args) {
		return vk::update_descriptor_sets(
			elements::vk::possibly_guarded_handle_of<vk::device>(args...),
			array{
				elements::of_type<vk::copy_descriptor_set>(args...)
			}
		);
	}

} // vk