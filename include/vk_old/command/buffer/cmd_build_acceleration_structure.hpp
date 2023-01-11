#pragma once

#include "handle.hpp"

#include "../../acceleration_structure/build_geometry_info.hpp"
#include "../../acceleration_structure/build_range_info.hpp"
#include "../../device/handle.hpp"
#include "../../device/get_proc_address.hpp"

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/range_of_value_type_same_as.hpp>

typedef void (VK_PTR* PFN_vkCmdBuildAccelerationStructuresKHR)(
	handle<vk::command_buffer> command_buffer,
	uint32 info_count,
	const vk::acceleration_structure_build_geometry_info* infos,
	const vk::acceleration_structure_build_range_info* const* build_range_infos
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		// TODO it should not be here
		types::are_contain_one_decayed<handle<vk::device>>,
		types::are_contain_one_decayed<handle<vk::command_buffer>>,
		// TODO zip em
		types::are_contain_range_of<
			vk::acceleration_structure_build_geometry_info
		>,
		types::are_contain_range_of<
			const vk::acceleration_structure_build_range_info*
		>
	>::for_types<Args...>
	void cmd_build_acceleration_structure(Args&&... args) {
		auto device = elements::decayed<handle<vk::device>>(args...);

		auto f = (PFN_vkCmdBuildAccelerationStructuresKHR)
			vk::get_device_proc_address(
				device,
				"vkCmdBuildAccelerationStructuresKHR"
			);

		auto command_buffer {
			elements::decayed<handle<vk::command_buffer>>(args...)
		};

		auto& infos {
			elements::range_of<
				vk::acceleration_structure_build_geometry_info
			>(args...)
		};

		auto& ranges {
			elements::range_of<
				const vk::acceleration_structure_build_range_info*
			>(args...)
		};

		f(
			command_buffer,
			infos.size(),
			infos.data(),
			ranges.data()
		);
	}

} // vk

template<typename... Args>
auto&
handle<vk::command_buffer>::cmd_build_acceleration_structure(
	Args&&... args
) const {
	vk::cmd_build_acceleration_structure(*this, forward<Args>(args)...);
	return *this;
}