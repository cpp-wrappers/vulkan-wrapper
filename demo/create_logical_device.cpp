#if 0
. `dirname $0`/build_and_run.sh create_logical_device
#endif

#include "vk/image/format.hpp"
#include "vk/image/layout.hpp"
#include "vk/queue_family_index.hpp"
#include "vk/render_pass.hpp"
//#include "vk/subpass_description.hpp"
//#include "vk/command_buffer_level.hpp"
#include "vk/instance/instance.hpp"
#include "vk/device_queue_create_info.hpp"
#include "vk/device/create.hpp"
//#include "vk/command_pool.hpp"

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

	/*vk::command_pool& command_pool = device.create_command_pool(
		vk::queue_family_index{ 0 }
	);

	vk::render_pass& render_pass = device.create_render_pass(
		vk::attachment_description {
			vk::format::r8_g8_b8_a8_unorm,
			vk::load_op{ vk::attachment_load_op::clear },
			vk::store_op{ vk::attachment_store_op::store },
			vk::final_layout{ vk::image_layout::color_attachment_optimal }
		},
		vk::subpass_description {}
	);

	std::cout << "done." << std::endl;*/
}