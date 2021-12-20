#include "handle.hpp"
#include "create.hpp"

namespace vk {
	class debug_report_callback_guard;

	class instance_guard {
		vk::instance instance;
	public:

		instance_guard(vk::instance instance)
			: instance{ instance }
		{}

		template<typename... Args>
		instance_guard(Args&&... args)
			: instance{ vk::create_instance(forward<Args>(args)...) }
		{}

		~instance_guard() {
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
		vk::debug_report_callback_guard create_guarded_debug_report_callback(Args&&... args) const;
	};
} // vk

#include "../debug/report/callback/guard.hpp"

template<typename... Args>
vk::debug_report_callback_guard vk::instance_guard::create_guarded_debug_report_callback(Args&&... args) const {
	return { instance.create_debug_report_callback(forward<Args>(args)...), this->instance };
}