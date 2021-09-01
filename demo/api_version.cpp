#if 0
. `dirname $0`/build_and_run.sh api_version
#endif

#include "vk/api_version.hpp"

int main() {
	vk::api_version {
		vk::major{ 1 },
		vk::minor{ 2 }
	};
}