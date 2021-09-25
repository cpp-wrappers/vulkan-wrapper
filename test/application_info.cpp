#include "vk/instance/application_info.hpp"

int main() {
	vk::application_info {
		vk::api_version {
			vk::major{ 1u },
			vk::minor{ 2u }
		}
	};

	vk::application_info {
		vk::api_version {
			vk::major{ 1u },
			vk::minor{ 2u }
		},
		vk::application_name{ "coolest engine" }
	};

	vk::application_info {
		vk::application_version{ 0u },
		vk::api_version {
			vk::major{ 1u },
			vk::minor{ 2u }
		},
		vk::application_name{ "coolest engine" }
	};

	vk::application_info {
		vk::application_version{ 0u },
		vk::api_version {
			vk::major{ 1u },
			vk::minor{ 2u }
		},
		vk::engine_name{ "coolest engine"},
		vk::engine_version{ 1u },
		vk::application_name{ "coolest app" }
	};
}