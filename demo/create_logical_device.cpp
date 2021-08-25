#include "vk/command_buffer_level.hpp"
#if 0
. `dirname $0`/build_and_run.sh create_logical_device
#endif

#include "vk/device_queue_create_info.hpp"
#include "vk/queue_family_properties.hpp"
#include "vk/device.hpp"
#include "vk/instance.hpp"
#include "vk/command_pool.hpp"
#include <iostream>

int main() {
	vk::instance i {
		vk::application_info{ vk::api_version{ vk::major{1}, vk::minor{0} } },
		vk::enabled_layer_name{ "VK_LAYER_KHRONOS_validation" }
	};

	vk::physical_device physical_device = i.first_physical_device();

	vk::device device {
		physical_device,
		vk::device_queue_create_info {
			vk::queue_family_index{ 0 },
			vk::queue_priorities{ 1.0F }
		}
	};

	vk::command_pool pool {
		device,
		vk::queue_family_index{ 0 }
	};

	auto b = pool.allocate_command_buffer(vk::command_buffer_level::primary);

	std::cout << "done." << std::endl;
}