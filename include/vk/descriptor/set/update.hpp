#pragma once

#include "write.hpp"
#include "copy.hpp"

#include "../../device/handle.hpp"
#include "../../function.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR void VK_CALL vkUpdateDescriptorSets(
	handle<vk::device> device,
	uint32 descriptor_write_count,
	const vk::write_descriptor_set* descriptor_writes,
	uint32 descriptor_copy_count,
	const vk::copy_descriptor_set* descriptor_copies
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_may_contain_range_of<vk::write_descriptor_set>,
		types::are_may_contain_range_of<vk::copy_descriptor_set>
	>::for_types<Args...>
	void update_descriptor_sets(Args&&... args) {
		auto device = elements::decayed<handle<vk::device>>(args...);

		uint32 write_count{};
		const vk::write_descriptor_set* writes;

		if constexpr (
			types::are_contain_range_of<
				vk::write_descriptor_set
			>::for_types<Args...>
		) {
			auto& writes0 {
				elements::range_of<vk::write_descriptor_set>(args...)
			};

			write_count = (uint32) writes0.size();
			writes = writes0.data();
		}

		uint32 copy_count{};
		const vk::copy_descriptor_set* copies;

		if constexpr (
			types::are_contain_range_of<
				vk::copy_descriptor_set
			>::for_types<Args...>
		) {
			auto& copies0 {
				elements::range_of<vk::copy_descriptor_set>(args...)
			};

			copy_count = (uint32) copies0.size();
			copies = copies0.data();
		}

		vkUpdateDescriptorSets(
			device,
			write_count,
			writes,
			copy_count,
			copies
		);
	}

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_contain_decayed<vk::write_descriptor_set>
	>::for_types<Args...>
	void update_descriptor_set(Args&&... args) {
		return vk::update_descriptor_sets(
			elements::decayed<handle<vk::device>>(args...),
			array {
				elements::decayed<vk::write_descriptor_set>(args...)
			}
		);
	}

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_contain_decayed<vk::copy_descriptor_set>
	>::for_types<Args...>
	void update_descriptor_set(Args&&... args) {
		return vk::update_descriptor_sets(
			elements::decayed<handle<vk::device>>(args...),
			array {
				elements::decayed<vk::copy_descriptor_set>(args...)
			}
		);
	}

} // vk