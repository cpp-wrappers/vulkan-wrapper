#include "vk/instance/instance.hpp"
#include "vk/instance/create_info.hpp"
#include <core/array.hpp>

int main() {
	//
	auto& instance0 = vk::create_instance();
	vk::destroy_instance(instance0);

	//
	auto& instance1 = vk::create_instance(
		vk::application_info {
			vk::api_version {
				vk::major{ 1u },
				vk::minor{ 2u }
			}
		}
	);

	vk::destroy_instance(instance1);

	//
	array extensions {
		vk::enabled_extension_name{"VK_KHR_xcb_surface"},
		vk::enabled_extension_name{"VK_KHR_surface"}
	};

	array layers {
		vk::enabled_layer_name{"VK_LAYER_KHRONOS_validation"}
	};

	auto& instance2 = vk::create_instance(
		extensions,
		layers
	);
	
	vk::destroy_instance(instance2);
}