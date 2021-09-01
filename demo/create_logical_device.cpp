#include "vk/attachment_description.hpp"
#include "vk/attachment_load_op.hpp"
#include "vk/attachment_store_op.hpp"
#include "vk/format.hpp"
#include "vk/queue_family_index.hpp"
#include "vk/render_pass.hpp"
#if 0
. `dirname $0`/build_and_run.sh create_logical_device
#endif

#include "vk/command_buffer_level.hpp"
#include "vk/instance.hpp"
#include "vk/device_queue_create_info.hpp"
#include "vk/queue_family_properties.hpp"
#include "vk/device.hpp"
#include "vk/command_pool.hpp"
#include <iostream>

int main() {
	vk::instance& instance = vk::create_instance(
		vk::application_info{ vk::api_version{ vk::major{1}, vk::minor{0} } },
		vk::enabled_layer_name{ "VK_LAYER_KHRONOS_validation" }
	);

	vk::physical_device& physical_device = instance.first_physical_device();

	float priorities[1]{ 1.0F };

	vk::device device = physical_device.create_device(
		vk::device_queue_create_info {
			vk::queue_family_index{ 0 },
			vk::queue_count{ 1 },
			vk::queue_priorities{ priorities }
		}
	);

	vk::command_pool& command_pool = device.create_command_pool(
		vk::queue_family_index{ 0 }
	);

	//auto b = pool.allocate_command_buffer(vk::command_buffer_level::primary);

	vk::render_pass& render_pass = device.create_render_pass(
		vk::attachment_description {
			vk::format::r8_g8_b8_a8_unorm,
			vk::load_op{ vk::attachment_load_op::clear },
			vk::store_op{ vk::attachment_store_op::store },
			vk::stencil_load_op{ vk::attachment_load_op::dont_care },
			vk::stencil_store_op{ vk::attachment_store_op::dont_care },
			vk::initial_layout{ vk::image_layout::undefined },
			vk::final_layout{ vk::image_layout::color_attachment_optimal }
		}
	);

	std::cout << "done." << std::endl;
}