#include "vk/queue_family_properties.hpp"
#if 0
. `dirname $0`/build_and_run.sh create_logical_device
#endif

#include "vk/device.hpp"
#include "vk/instance.hpp"
#include <iostream>

int main() {
	vk::instance i {
		vk::application_info{ vk::api_version{ vk::major{1}, vk::minor{0} } }
	};

	vk::physical_device physical_device;
	i.view_physical_devices([&](auto& devices) {
		physical_device = devices.front();
	});

	float priorities[1]{1};

	vk::device device {
		physical_device,
		vk::device_queue_create_info {
			vk::queue_family_index{0},
			vk::queue_count{ 1 },
			vk::queue_priorities{ priorities }
		}
	};

	std::cout << "device created." << std::endl;
}