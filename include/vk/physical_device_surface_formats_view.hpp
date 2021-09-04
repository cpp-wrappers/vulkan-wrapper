#pragma once

#include <cstdint>
#include <ranges>
#include <vulkan/vulkan_core.h>

#include "surface_format.hpp"

namespace vk {

struct physical_device;
struct surface;

void view_physical_device_surface_formats(const vk::physical_device&, vk::surface&, uint32_t, auto&&);

class physical_device_surface_formats_view
	: public std::ranges::view_interface<physical_device_surface_formats_view>
{
	vk::surface_format* formats;
	uint32_t count;

	physical_device_surface_formats_view(
		vk::surface_format* formats,
		uint32_t count
	) : formats{ formats }, count{ count }
	{}

	friend void vk::view_physical_device_surface_formats(const vk::physical_device&, vk::surface&, uint32_t, auto&&);

public:
	vk::surface_format* begin() const {
		return formats;
	}

	vk::surface_format* end() const {
		return formats + count;
	}
};

void view_physical_device_surface_formats(
	const vk::physical_device& device,
	vk::surface& surface,
	uint32_t count,
	auto&& f
) {
	vk::surface_format formats[count];

	vkGetPhysicalDeviceSurfaceFormatsKHR(
		(VkPhysicalDevice)&device,
		(VkSurfaceKHR)&surface,
		&count,
		(VkSurfaceFormatKHR*) formats
	);

	physical_device_surface_formats_view v {
		formats, count
	};

	f(v);
}

}