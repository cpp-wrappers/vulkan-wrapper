#pragma once

#include "../../../object/destroy_or_free.hpp"
#include "../../device/handle.hpp"

namespace vk {

	template<>
	struct vk::destroy_t<vk::pipeline_layout> {

		template<typename... Args>
		void operator () (Args&&... args) const {
			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);
			auto layout = elements::of_type<vk::handle<vk::pipeline_layout>>(args...);

			vkDestroyPipelineLayout(
				(VkDevice) vk::get_handle_value(device),
				(VkPipelineLayout) vk::get_handle_value(layout),
				(VkAllocationCallbacks*) nullptr
			);
		}

	};

} // vk