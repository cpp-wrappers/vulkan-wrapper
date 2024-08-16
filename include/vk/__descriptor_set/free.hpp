#pragma once

#include <range.hpp>
#include <__range/of_element_type_satisfying_predicate.hpp>
#include "../__internal/function.hpp"
#include "../__device/handle.hpp"
#include "../__descriptor_pool/handle.hpp"
#include "./handle.hpp"

namespace vk {

	struct free_descriptor_sets_function : vk::function<void(*)(
		handle<vk::device>::underlying_type,
		handle<vk::descriptor_pool>::underlying_type,
		uint32 count,
		handle<vk::descriptor_set>
	)> {
		static constexpr auto name = "vkFreeDescriptorSets";
	};

	void free_descriptor_sets(
		handle<vk::instance> instance,
		handle<vk::device> device,
		handle<vk::descriptor_pool> descriptor_pool,
		range_of<is_same_as<handle<vk::descriptor_set>>.decayed> auto descriptor_sets
	) {
		vk::get_device_function<vk::free_descriptor_sets_function>(
			instance, device
		)(
			device.underlying(),
			descriptor_pool.underlying(),
			(uint32) descriptor_sets.size(),
			descriptor_sets.iterator()
		);
	}

} // vk