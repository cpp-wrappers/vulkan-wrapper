#include <vulkan/vulkan_core.h>
#if 0
. `dirname $0`/build_and_run.sh physical_devices_count
#endif

#include <stdio.h>
#include "vk/instance.hpp"

int main() {
	printf("%d\n", vk::instance{}.physical_devices_count());
}