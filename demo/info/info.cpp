#if 0
. ./`dirname ${BASH_SOURCE[0]}`/../build.sh $@
exit 1
#endif

#include "vk/instance/guard.hpp"
#include "vk/physical_device/handle.hpp"

#include "../platform/platform.hpp"

static nuint tabs = 0u;

void print(auto... vs) {
	for(nuint i = 0; i < tabs; ++i) platform::info((char) '\t');
	(platform::info(vs), ... );
}

void println(auto... vs) {
	print(vs...);
	platform::info((char)'\n');
}

template<bool t>
void block(char open, char close, auto f) {
	if(t) println(open);
	else {
		platform::info(open);
		platform::info((char)'\n');
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

int entrypoint() {
	vk::instance_guard instance {
		vk::create_instance(
			vk::application_info {
				vk::api_version {
					vk::major{ 1 }, vk::minor{ 0 }
				}
			}/*,
			array{ vk::layer_name{ "VK_LAYER_KHRONOS_validation" } }*/
		)
	};

	print("instance is created\n");

	array_block("physical devices", [&]() {
		instance.for_each_physical_device([](vk::physical_device& device) {
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

			array_block("queue family properties", [&]{
				device.for_each_queue_family_properties([](auto props) {
					object_block([&]{
						println("count: ", props.count);
						println(
							"min image transfer granularity: ",
							props.min_image_transfer_granularity[0u], ", ", 
							props.min_image_transfer_granularity[1u], ", ",
							props.min_image_transfer_granularity[2u]
						);
						println("graphics: ", props.flags.get(vk::queue_flag::graphics));
						println("compute: ", props.flags.get(vk::queue_flag::compute));
						println("transfer: ", props.flags.get(vk::queue_flag::transfer));
						println("tsparse binding: ", props.flags.get(vk::queue_flag::sparse_binding));
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

		/*array_block("layers", [&]{
			vk::for_each_layer_properties([](auto props) {
				object_block([&]{
					println("name: ", props.name);
					println("spec version: ", props.spec_version);
					println("implementation version: ", props.implementation_version);
					println("description: ", props.description);
				});
			});
		});*/
	});

	return 0;
}