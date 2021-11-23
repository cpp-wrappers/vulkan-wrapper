#include "handle.hpp"

namespace vk {
	class instance_guard {
		vk::instance instance;
	public:

		instance_guard(vk::instance instance)
			: instance{ instance }
		{}

		~instance_guard() {
			if(instance.handle) {
				vkDestroyInstance(
					(VkInstance) exchange(instance.handle, nullptr),
					nullptr
				);
			}
		}

		vk::instance object() const {
			return instance;
		}

		template<type::range_of_value_type<vk::physical_device> PhysicalDevices>
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
	};

}