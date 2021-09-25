#include "vk/instance/api_version.hpp"

int main() {
	vk::api_version {
		vk::major{ 1u },
		vk::minor{ 2u }
	};
}