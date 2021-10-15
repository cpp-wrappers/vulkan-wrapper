#if 0
. `dirname $0`/build_and_run.sh create_logical_device
#endif

#include "stdio.h"
#include "vk/instance/instance.hpp"
#include "vk/instance/destroy.hpp"

#include "vk/device/create.hpp"
#include "vk/device/destroy.hpp"

#include "vk/command/pool/create.hpp"
#include "vk/command/pool/destroy.hpp"

#include "vk/render_pass/create.hpp"
#include "vk/render_pass/destroy.hpp"

int main() {
	vk::instance& instance = vk::create_instance(
		vk::application_info{ vk::api_version{ vk::major{1u}, vk::minor{0u} } },
		array{ vk::enabled_layer_name{ "VK_LAYER_KHRONOS_validation" } }
	);

	vk::physical_device& physical_device = instance.first_physical_device();

	array priorities{ 1.0F };

	vk::device& device = vk::create_device(
		physical_device,
		array{
			vk::device_queue_create_info {
				vk::queue_family_index{ 0u },
				vk::queue_count{ 1u },
				vk::queue_priorities{ priorities.data() }
			}
		}
	);

	vk::command_pool& command_pool = vk::create_command_pool(
		device,
		vk::queue_family_index{ 0u }
	);

	vk::render_pass& render_pass = vk::create_render_pass(
		device,
		array {
			vk::attachment_description {
				vk::format::r8_g8_b8_a8_unorm,
				vk::load_op{ vk::attachment_load_op::clear },
				vk::store_op{ vk::attachment_store_op::store },
				vk::final_layout{ vk::image_layout::color_attachment_optimal }
			}
		},
		array {
			vk::subpass_description {}
		}
	);

	vk::destroy_render_pass(device, render_pass);
	vk::destroy_command_pool(device, command_pool);
	vk::destroy_device(device);
	vk::destroy_instance(instance);

	printf("done.\n");
}