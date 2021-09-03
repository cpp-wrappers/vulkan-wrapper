#include "vk/device_queue_create_info.hpp"
#include "vk/queue_family_index.hpp"

int main() {
	float priorities[] = { 1.0F };

	vk::device_queue_create_info {
		vk::queue_family_index{0},
		vk::queue_priorities{ priorities },
		vk::queue_count{ 1 }
	};
}