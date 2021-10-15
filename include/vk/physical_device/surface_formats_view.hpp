#pragma once

#include <core/integer.hpp>
#include "../surface/format.hpp"

namespace vk {

struct physical_device;
struct surface;

void view_physical_device_surface_formats(const vk::physical_device&, vk::surface&, uint32, auto&&);

class physical_device_surface_formats_view {
	vk::surface_format* formats;
	uint32 count;

	physical_device_surface_formats_view(
		vk::surface_format* formats,
		uint32 count
	) : formats{ formats }, count{ count }
	{}

	friend void vk::view_physical_device_surface_formats(const vk::physical_device&, vk::surface&, uint32, auto&&);

public:
	vk::surface_format* begin() const {
		return formats;
	}

	vk::surface_format* end() const {
		return formats + (primitive::uint32) count;
	}

	vk::surface_format& front() const {
		return *begin();
	}
};

void view_physical_device_surface_formats(
	const vk::physical_device& device,
	vk::surface& surface,
	uint32 count,
	auto&& f
) {
	vk::surface_format formats[(primitive::uint32) count];

	vkGetPhysicalDeviceSurfaceFormatsKHR(
		(VkPhysicalDevice)&device,
		(VkSurfaceKHR)&surface,
		(primitive::uint32*) &count,
		(VkSurfaceFormatKHR*) formats
	);

	physical_device_surface_formats_view v {
		formats, count
	};

	f(v);
}

}