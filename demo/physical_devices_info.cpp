#if 0
. `dirname $0`/build_and_run.sh physical_devices_info
#endif

#include <iostream>
#include "vk/instance.hpp"

int main() {
	vk::instance i {
		vk::application_info{ vk::api_version{ vk::major{1}, vk::minor{0} } }
	};

	i.view_physical_devices([](auto& devices) {
		for(vk::physical_device device : devices) {
			auto props = device.properties();

			std::cout << "api version: "
				<< props.api_version.variant() << "."
				<< props.api_version.major() << "."
				<< props.api_version.minor() << "."
				<< props.api_version.patch() << std::endl
			;

			std::cout
				<< "driver version: " << props.driver_version << std::endl
				<< "vendor id: " << props.vendor_id << std::endl
				<< "device id: " << props.device_id << std::endl
			;

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

			std::cout << "device type: " << type_name << std::endl;
			std::cout << "name: " << props.name << std::endl;

			std::cout << "queue families properties: {" << std::endl;
			device.view_queue_families_properties([](auto& queue_families_props) {
				for(auto& family_props : queue_families_props) {
					std::cout << "\t" << queue_families_props.index(family_props) << ": {" << std::endl;
					std::cout << "\t\t" << "count: " << family_props.count << std::endl
						<< "\t\tmin image transfer granularity: "
							<< family_props.min_image_transfer_granularity[0] << " "
							<< family_props.min_image_transfer_granularity[1] << " "
							<< family_props.min_image_transfer_granularity[2] << std::endl
						<< "\t\tgraphics: " << family_props.flags.get(vk::queue_flag::graphics) << std::endl
						<< "\t\tcompute: " << family_props.flags.get(vk::queue_flag::compute) << std::endl
						<< "\t\ttransfer: " << family_props.flags.get(vk::queue_flag::transfer) << std::endl
						<< "\t\tsparse binding: " << family_props.flags.get(vk::queue_flag::sparse_binding) << std::endl
					;
					std::cout << "\t}" << std::endl;
				}
			});
			std::cout << "}" << std::endl;

			std::cout << "extensions properties: {" << std::endl;
			device.view_extensions_properties([](auto& extensions_props) {
				for(auto ex_props : extensions_props) {
					std::cout << "\tname: " << ex_props.name
						<< ", spec version: " << ex_props.spec_version << std::endl;
				}
			});
			std::cout << "}" << std::endl;
		}
	});

	
}