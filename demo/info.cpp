#if 0
. `dirname $0`/build_and_run.sh info
#endif

#include "vk/instance.hpp"
#include "vk/instance_guard.hpp"
#include "vk/physical_device.hpp"

#include <stdio.h>
#include <string.h>
#include <core/number.hpp>

static uint tabs = 0u;

void print_atom(char str) {
	putc(str, stdout);
}

void print_atom(const char* str) {
	fwrite(str, 1, strlen(str), stdout);
}

void print_atom(char* str) {
	fwrite(str, 1, strlen(str), stdout);
}

template<unsigned_integer I>
void print_atom(I i) {
	for_each_digit_in_number(number{ i }, base{ 10 }, [](uint digit) {
		print_atom(char(digit + '0'));
	});
}

void print_atom(bool b) {
	if(b) print_atom("true");
	else print_atom("false");
}

void print(auto... vs) {
	for(uint i = 0; i < tabs; ++i) print_atom((char) '\t');
	(print_atom(vs), ... );
}

void println(auto... vs) {
	print(vs...);
	print_atom((char)'\n');
}

template<bool t>
void block(char open, char close, auto f) {
	if(t) println(open);
	else {
		print_atom(open);
		print_atom((char)'\n');
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

int main() {
	vk::instance_guard instance {
		vk::create_instance(
			vk::application_info {
				vk::api_version {
					vk::major{ 1 }, vk::minor{ 0 }
				}
			},
			array{ vk::layer_name{ "VK_LAYER_KHRONOS_validation" } }
		)
	};

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
}