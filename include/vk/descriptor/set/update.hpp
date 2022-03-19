#pragma once

#include "write.hpp"
#include "copy.hpp"

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

#include "vk/device/handle.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_may_contain_range_of<vk::write_descriptor_set>,
		types::are_may_contain_range_of<vk::copy_descriptor_set>
	>::for_types<Args...>
	void update_descriptor_sets(Args&&... args) {
		auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);

		uint32 write_count{};
		const vk::write_descriptor_set* writes;

		if constexpr(types::are_contain_range_of<vk::write_descriptor_set>::for_types<Args...>) {
			auto& writes0 = elements::range_of<vk::write_descriptor_set>(args...);
			write_count = (uint32) writes0.size();
			writes = writes0.data();
		}

		uint32 copy_count{};
		const vk::copy_descriptor_set* copies;

		if constexpr(types::are_contain_range_of<vk::copy_descriptor_set>::for_types<Args...>) {
			auto& copies0 = elements::range_of<vk::copy_descriptor_set>(args...);
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
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_decayed<vk::write_descriptor_set>
	>::for_types<Args...>
	void update_descriptor_set(Args&&... args) {
		return vk::update_descriptor_sets(
			elements::possibly_guarded_handle_of<vk::device>(args...),
			array{
				elements::decayed<vk::write_descriptor_set>(args...)
			}
		);
	}

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_decayed<vk::copy_descriptor_set>
	>::for_types<Args...>
	void update_descriptor_set(Args&&... args) {
		return vk::update_descriptor_sets(
			elements::possibly_guarded_handle_of<vk::device>(args...),
			array{
				elements::decayed<vk::copy_descriptor_set>(args...)
			}
		);
	}

} // vk