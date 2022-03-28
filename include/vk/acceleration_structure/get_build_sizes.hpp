#pragma once

#include "build_geometry_info.hpp"
#include "build_sizes_info.hpp"
#include "build_type.hpp"

#include "vk/device/handle.hpp"
#include "vk/headers.hpp"

namespace vk {

	template<possibly_guarded_handle_of<vk::device> Device>
	vk::acceleration_structure_build_sizes_info
	get_acceleration_structure_build_sizes(
		Device&& device,
		vk::acceleration_structure_build_type build_type,
		const vk::acceleration_structure_build_geometry_info& geometry_info,
		const uint32* max_primitive_counts
	) {
		vk::acceleration_structure_build_sizes_info build_sizes_info{};

		auto f {
			(PFN_vkGetAccelerationStructureBuildSizesKHR) vkGetDeviceProcAddr(
				(VkDevice) vk::get_handle_value(device),
				"vkGetAccelerationStructureBuildSizesKHR"
			)
		};

		f(
			(VkDevice) vk::get_handle_value(device),
			(VkAccelerationStructureBuildTypeKHR) build_type,
			(const VkAccelerationStructureBuildGeometryInfoKHR*) &geometry_info,
			(const uint32_t*) max_primitive_counts,
			(VkAccelerationStructureBuildSizesInfoKHR*) &build_sizes_info
		);

		return build_sizes_info;
	}

	template<typename... Args>
	vk::acceleration_structure_build_sizes_info
	get_build_sizes(Args&&... args) {
		return vk::get_acceleration_structure_build_sizes(forward<Args>(args)...);
	}

} // vk