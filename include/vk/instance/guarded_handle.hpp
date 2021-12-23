#pragma once

#include "handle.hpp"
#include "create.hpp"
#include "../shared/guarded_handle.hpp"

namespace vk {
	class debug_report_callback_guard;

	template<>
	struct guarded_handle<vk::instance> : vk::guarded_handle_base<vk::instance> {

		~guarded_handle() {
			if(handle().value) {
				vkDestroyInstance(
					(VkInstance) exchange(handle().value, nullptr),
					nullptr
				);
			}
		}

		template<range::of_value_type<vk::physical_device> PhysicalDevices>
		elements::one_of<vk::result, vk::count>
		try_enumerate_physical_devices(PhysicalDevices&& devices) const {
			return handle().try_enumerate_physical_devices(forward<PhysicalDevices>(devices));
		}

		vk::handle<vk::physical_device> get_first_physical_device() const {
			return handle().get_first_physical_device();
		}

		template<typename F>
		vk::count for_each_physical_device(F&& f) const {
			return handle().for_each_physical_device(forward<F>(f));
		}

		template<typename... Args>
		vk::guarded_handle<vk::debug_report_callback> create_guarded_debug_report_callback(Args&&... args) const;
	};

	template<typename... Args>
	vk::guarded_handle<vk::instance> create_guarded_instance(Args&&... args) {
		return { vk::create_instance(forward<Args>(args)...) };
	}
} // vk

#include "../debug/report/callback/guarded_handle.hpp"

template<typename... Args>
vk::guarded_handle<vk::debug_report_callback> vk::guarded_handle<vk::instance>::create_guarded_debug_report_callback(Args&&... args) const {
	return { handle().create_debug_report_callback(forward<Args>(args)...), handle() };
}