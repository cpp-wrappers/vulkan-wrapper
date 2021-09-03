#include "vk/application_info.hpp"
#include "vk/api_version.hpp"

int main() {
	vk::application_info {
		vk::api_version {
			vk::major{ 1 },
			vk::minor{ 2 }
		}
	};

	vk::application_info {
		vk::api_version {
			vk::major{ 1 },
			vk::minor{ 2 }
		},
		vk::application_name{ "coolest engine" }
	};

	vk::application_info {
		vk::application_version{ 0 },
		vk::api_version {
			vk::major{ 1 },
			vk::minor{ 2 }
		},
		vk::application_name{ "coolest engine" }
	};

	vk::application_info {
		vk::application_version{ 0 },
		vk::api_version {
			vk::major{ 1 },
			vk::minor{ 2 }
		},
		vk::engine_name{ "coolest engine"},
		vk::engine_version{ 1 },
		vk::application_name{ "coolest app" }
	};
}