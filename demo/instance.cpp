#if 0
. `dirname $0`/build_and_run.sh instance
#endif
#include "vk/instance.hpp"

int main() {
	vk::instance {
	};

	vk::instance {
		vk::application_info {
			vk::api_version {
				vk::major{1},
				vk::minor{1}
			}
		}
	};

}