#pragma once

#include "headers.hpp"
#include "pipeline_layout_create_info.hpp"
#include "vk/descriptor_set_layout.hpp"
#include "vk/push_constant_range.hpp"
#include <cxx_util/params.hpp>
#include <vulkan/vulkan_core.h>
#include "result.hpp"

namespace vk {

struct pipeline_layout {
	VkPipelineLayout m_pipeline_layout;

	template<typename... Ps>
	pipeline_layout(Ps&&... params) {
		vk::pipeline_layout_create_info ci{};

		u::params<Ps&...> ps{ params... };

		ci.m_descriptor_set_layout_count = ps.template count<vk::descriptor_set_layout&>;
		ci.m_push_constant_range_count = ps.template count<vk::push_constant_range&>;

		vk::descriptor_set_layout dsls[ci.m_descriptor_set_layout_count.value];
		vk::push_constant_range pcrs[ci.m_push_constant_range_count.value];

		uint32_t current_dls = 0, current_pcr = 0;
		VkDevice device;

		ps
			.template handle<u::required>([&](vk::device& d){ device = d.m_device; })
			.template handle<u::any>([&](vk::descriptor_set_layout& dsl){ dsls[current_dls++] = dsl; })
			.template handle<u::any>([&](vk::push_constant_range& pcr){ pcrs[current_pcr++] = pcr; })
			.check_for_emptiness();

		vk::throw_if_error(
			vkCreatePipelineLayout(
				device,
				(VkPipelineLayoutCreateInfo*)&ci,
				nullptr,
				&m_pipeline_layout
			)
		);
	}
};

}