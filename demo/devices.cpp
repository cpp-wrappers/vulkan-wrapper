#if 0
pushd `dirname $0`
cd ..
bash prebuild.sh
mkdir -p build
clang++ --config ./compile_flags.txt -lvulkan -o build/devices demo/devices.cpp
./build/devices
popd
exit 0
#endif
import vk.instance;
import <iostream>;

int main() {
	vk::instance i {
		vk::application_info{ vk::api_version{ vk::major{1}, vk::minor{0} } }
	};

	for(vk::physical_device device : i.physical_devices()) {
		//VkPhysicalDeviceProperties props;
		auto props = device.properties();
		//vkGetPhysicalDeviceProperties(device, &props);

		std::cout << "api version: "
			<< props.api_version.variant() << "."
			<< props.api_version.major() << "."
			<< props.api_version.minor() << "."
			<< props.api_version.patch() << std::endl;
		std::cout << "driver version: " << props.driver_version << std::endl;
		std::cout << "vendor id: " << props.vendor_id << std::endl;
		std::cout << "device id: " << props.device_id << std::endl;

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
		for(auto family_props : device.queue_families_properties()) {
			std::cout << "\t{" << std::endl;
			std::cout << "\t\t" << "count: " << family_props.count << std::endl
				<< "\t\tgraphics: " << family_props.flags.get(vk::queue_flag::graphics) << std::endl
				<< "\t\tcompute: " << family_props.flags.get(vk::queue_flag::compute) << std::endl
				<< "\t\ttransfer: " << family_props.flags.get(vk::queue_flag::transfer) << std::endl
				<< "\t\tsparse binding: " << family_props.flags.get(vk::queue_flag::sparse_binding) << std::endl
			;
			std::cout << "\t}" << std::endl;
		}
		std::cout << "}" << std::endl;
	}
}