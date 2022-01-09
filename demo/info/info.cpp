#if 0
. ./`dirname ${BASH_SOURCE[0]}`/../build.sh $@
exit 0
#endif

#include "vk/instance/guarded_handle.hpp"
#include "vk/physical_device/handle.hpp"
#include "vk/instance/layer_properties.hpp"
#include "../platform/platform.hpp"
#include <string.h>

static nuint tabs = 0u;

void print(auto... vs) {
	for(nuint i = 0; i < tabs; ++i) platform::info('\t');
	platform::info(vs...);
}

void println(auto... vs) {
	print(vs...);
	platform::info.new_line();
}

template<bool t>
void block(char open, char close, auto f) {
	if(t) println(open);
	else {
		platform::info(open, '\n');
		platform::info('\n');
	}

	++tabs;
	f();
	--tabs;

	println(close);
}

void array_block(auto name, auto f) {
	print(name, ": ");
	block<false>('[', ']', f);
}

void object_block(auto f) {
	block<true>('{', '}', f);
}

void object_block(auto name, auto f) {
	print(name, ": ");
	object_block(f);
}

void entrypoint() {
	vk::layer_name validation_layer_name{ "VK_LAYER_KHRONOS_validation" };
	bool validation_layer_is_supported = vk::is_instance_layer_supported(validation_layer_name);

	span<vk::layer_name> layers{ validation_layer_is_supported ? &validation_layer_name : nullptr, validation_layer_is_supported ? 1u : 0u };

	auto instance = vk::create_guarded_instance(layers);

	array_block("physical devices", [&]() {
		instance.for_each_physical_device([](vk::handle<vk::physical_device> device) {
			auto props = device.get_properties();

			println("api version: ",
				props.api_version.variant, ".",
				props.api_version.major, ".",
				props.api_version.minor, ".",
				props.api_version.patch
			);

			println("driver version: ", props.driver_version);
			println("vendor id: ", props.vendor_id);
			println("device id: ", props.device_id);

			const char* type_name;
			switch(props.type) {
				case vk::physical_device_type::other
					: type_name = "other"; break;
				case vk::physical_device_type::integrated_gpu
					: type_name = "integrated gpu"; break;
				case vk::physical_device_type::discrete_gpu
					: type_name = "discrete gpu"; break;
				case vk::physical_device_type::virtual_gpu
					: type_name = "virtual gpu"; break;
				case vk::physical_device_type::cpu
					: type_name = "cpu"; break;
			}

			println("device type: ", type_name);
			println("name: ", props.name);

			array_block("queue family properties", [&] {
				device.for_each_queue_family_properties([](auto props) {
					object_block([&]{
						println("count: ", props.count);
						println(
							"min image transfer granularity: ",
							props.min_image_transfer_granularity[0], ", ", 
							props.min_image_transfer_granularity[1], ", ",
							props.min_image_transfer_granularity[2]
						);
						println("graphics: ", props.flags.get(vk::queue_flag::graphics));
						println("compute: ", props.flags.get(vk::queue_flag::compute));
						println("transfer: ", props.flags.get(vk::queue_flag::transfer));
						println("sparse binding: ", props.flags.get(vk::queue_flag::sparse_binding));
					});
				});
			});

			array_block("device extensions properties", [&] {
				device.for_each_extension_properties([](auto props) {
					object_block([&]{
						println("name: ", props.name);
						println("spec version: ", props.spec_version);
					});
				});
			});
		});

		array_block("instance_layers", [&] {
			vk::for_each_instance_layer_properties([](auto props) {
				object_block([&]{
					println("name: ", props.name);
					println("spec version: ", props.spec_version);
					println("implementation version: ", props.implementation_version);
					println("description: ", props.description);
				});
			});
		});
	});
}