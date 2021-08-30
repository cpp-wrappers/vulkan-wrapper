#if 0
. `dirname $0`/build_and_run.sh info
#endif

#include <iostream>
#include "vk/instance.hpp"
#include "vk/layer_properties_view.hpp"

static std::size_t tabs = 0;

void print(auto... vs) {
	char tabs_chars[tabs + 1];
	std::fill_n(tabs_chars, tabs, '\t');
	tabs_chars[tabs] = 0;

	std::cout << tabs_chars;
	(std::cout << ... << vs );
}

void println(auto... vs) {
	print(vs...);
	std::cout << "\n";
}

void block(char open, char close, auto f) {
	println(open);

	++tabs;
	f();
	--tabs;
	println(close);
}

void array_block(auto name, auto f) {
	print(name, ": ");
	block('[', ']', f);
}

void object_block(auto f) {
	block('{', '}', f);
}

int main() {
	vk::instance i {
		vk::application_info{ vk::api_version{ vk::major{1}, vk::minor{0} } }
	};

	array_block("physical devices", [&]() {
		i.for_each_physical_device([](auto& device) {
			auto props = device.properties();

			println("api version: ",
				props.api_version.variant().value, ".",
				props.api_version.major().value, ".",
				props.api_version.minor().value, ".",
				props.api_version.patch().value
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
				device.for_each_queue_family_properties([](auto& props) {
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
						println("tsparse binding: ", props.flags.get(vk::queue_flag::sparse_binding));
					});
				});
			});

			array_block("device extensions properties", [&]{;
				device.for_each_extension_properties([](auto& props) {
					object_block([&]{
						println("name: ", props.name);
						println("spec version: ", props.spec_version);
					});
				});
			});
		});

		array_block("layers", [&]{
			vk::for_each_layer_properties([](auto& props) {
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