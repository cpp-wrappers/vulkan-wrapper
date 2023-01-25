#pragma once

#include "build_geometry_info.hpp"
#include "build_sizes_info.hpp"
#include "build_type.hpp"

#include "../device/handle.hpp"
#include "../device/get_proc_address.hpp"
#include "../function.hpp"

typedef void (VK_PTR *PFN_vkGetAccelerationStructureBuildSizesKHR)(
	handle<vk::device> device,
	vk::acceleration_structure_build_type buildType,
	const vk::acceleration_structure_build_geometry_info* build_info,
	const uint32* pMaxPrimitiveCounts,
	vk::acceleration_structure_build_sizes_info* size_info
);

namespace vk {

	vk::acceleration_structure_build_sizes_info inline
	get_acceleration_structure_build_sizes(
		handle<vk::device> device,
		vk::acceleration_structure_build_type build_type,
		const vk::acceleration_structure_build_geometry_info& geometry_info,
		const uint32* max_primitive_counts
	) {
		vk::acceleration_structure_build_sizes_info build_sizes_info{};

		auto f {
			(PFN_vkGetAccelerationStructureBuildSizesKHR)
			vk::get_device_proc_address(
				device, "vkGetAccelerationStructureBuildSizesKHR"
			)
		};

		f(
			device, build_type,
			&geometry_info,
			max_primitive_counts,
			&build_sizes_info
		);

		return build_sizes_info;
	}

	template<typename... Args>
	vk::acceleration_structure_build_sizes_info
	get_build_sizes(Args&&... args) {
		return vk::get_acceleration_structure_build_sizes(forward<Args>(args)...);
	}

} // vk