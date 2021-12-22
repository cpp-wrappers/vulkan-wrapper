#pragma once

#include "handle.hpp"
#include "create.hpp"
#include "../shared/guarded.hpp"

namespace vk {
	class debug_report_callback_guard;

	template<>
	class guarded<vk::instance> {
		vk::instance instance;
	public:

		guarded(vk::instance instance)
			: instance{ instance }
		{}

		guarded(guarded&& other)
			: instance{ exchange(other.instance.handle, nullptr) }
		{}

		~guarded() {
			if(instance.handle) {
				vkDestroyInstance(
					(VkInstance) exchange(instance.handle, nullptr),
					nullptr
				);
			}
		}

		const vk::instance& object() const {
			return instance;
		}

		template<range::of_value_type<vk::physical_device> PhysicalDevices>
		elements::one_of<vk::result, vk::count> try_enumerate_physical_devices(PhysicalDevices&& devices) const {
			return instance.try_enumerate_physical_devices(forward<PhysicalDevices>(devices));
		}

		vk::physical_device get_first_physical_device() const {
			return instance.get_first_physical_device();
		}

		template<typename F>
		vk::count for_each_physical_device(F&& f) const {
			return instance.for_each_physical_device(forward<F>(f));
		}

		template<typename... Args>
		vk::guarded<vk::debug_report_callback> create_guarded_debug_report_callback(Args&&... args) const;
	};

	template<typename... Args>
	vk::guarded<vk::instance> create_guarded_instance(Args&&... args) {
		return { vk::create_instance(forward<Args>(args)...) };
	}
} // vk

#include "../debug/report/callback/guard.hpp"

template<typename... Args>
vk::guarded<vk::debug_report_callback> vk::guarded<vk::instance>::create_guarded_debug_report_callback(Args&&... args) const {
	return { instance.create_debug_report_callback(forward<Args>(args)...), this->instance };
}