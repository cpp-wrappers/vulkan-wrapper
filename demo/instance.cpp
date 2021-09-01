#if 0
. `dirname $0`/build_and_run.sh instance
#endif
#include "vk/instance.hpp"

int main() {
	auto& instance0 = vk::create_instance();

	auto& instance1 = vk::create_instance(
		vk::application_info {
			vk::api_version {
				vk::major{1},
				vk::minor{2}
			}
		}
	);

	vk::destroy_instance(instance0);
	vk::destroy_instance(instance1);
}