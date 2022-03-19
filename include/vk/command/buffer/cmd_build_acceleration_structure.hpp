#pragma once

#include "handle.hpp"

#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/range/of_value_type_same_as.hpp>

#include "vk/acceleration_structure/build_geometry_info.hpp"
#include "vk/acceleration_structure/build_range_info.hpp"
#include "vk/device/handle.hpp"
#include <core/handle/possibly_guarded_of.hpp>

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		// TODO it should not be here
		types::are_contain_one_possibly_guarded_handle_of<vk::device>,
		types::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		// TODO zip em
		types::are_contain_one_range_of<vk::acceleration_structure_build_geometry_info>,
		types::are_contain_one_range_of<const vk::acceleration_structure_build_range_info*>
	>::for_types<Args...>
	void cmd_build_acceleration_structure(Args&&... args) {
		auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);

		auto f = (PFN_vkCmdBuildAccelerationStructuresKHR)
			vkGetDeviceProcAddr(
				(VkDevice) vk::get_handle_value(device),
				"vkCmdBuildAccelerationStructuresKHR"
			);

		auto& command_buffer = elements::possibly_guarded_handle_of<vk::command_buffer>(args...);

		auto& infos = elements::range_of<vk::acceleration_structure_build_geometry_info>(args...);
		auto& ranges = elements::range_of<const vk::acceleration_structure_build_range_info*>(args...);

		f(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			infos.size(),
			(const VkAccelerationStructureBuildGeometryInfoKHR*) infos.data(),
			(const VkAccelerationStructureBuildRangeInfoKHR* const*) ranges.data()
		);
	}

} // vk

template<typename... Args>
auto& handle<vk::command_buffer>::cmd_build_acceleration_structure(Args&&... args) const {
	vk::cmd_build_acceleration_structure(*this, forward<Args>(args)...);
	return *this;
}