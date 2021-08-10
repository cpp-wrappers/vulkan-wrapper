#if 0
pushd `dirname $0`
cd ..
bash prebuild.sh
mkdir -p build
clang++ --config ./compile_flags.txt -lvulkan -o build/devices demo/devices.cpp
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

		//vkGetPhysicalDeviceProperties(device, &props);

		//std::cout << "api version: " << props.apiVersion << std::endl;
		//std::cout << "driver version: " << props.driverVersion << std::endl;
		//std::cout << "name: " << props.deviceName << std::endl;
	}
}