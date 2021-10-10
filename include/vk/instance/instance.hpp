#pragma once

#include <core/integer.hpp>
#include <core/forward.hpp>

#include "physical_devices_view.hpp"
#include "create.hpp"
#include "destroy.hpp"

namespace vk {

class instance {
	instance() = delete;
	instance(const instance&) = delete;
public:

	uint32 physical_devices_count() const {
		uint32 count;
		vk::throw_if_error(
			vkEnumeratePhysicalDevices(
				(VkInstance)this,
				&((primitive::uint32&)count),
				nullptr
			)
		);
		return count;
	}

	template<typename F>
	void view_physical_devices(uint32 count, F&& f) const {
		view_instance_physical_devices(
			count,
			(VkInstance)this,
			forward<F>(f)
		);
	}

	template<typename F>
	void view_physical_devices(F&& f) const {
		view_physical_devices(
			physical_devices_count(),
			forward<F>(f)
		);
	}

	vk::physical_device& first_physical_device() {
		vk::physical_device* ptr;

		view_physical_devices(1u, [&](auto& devices) {
			ptr = &devices.front();
		});

		return *ptr;
	}

	void for_each_physical_device(auto&& f) {
		view_physical_devices([&](vk::physical_devices_view& view) {
			for(vk::physical_device& device : view) f(device);
		});
	}
}; // instance

} // vk