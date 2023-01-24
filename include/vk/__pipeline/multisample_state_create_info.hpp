#pragma once

#include "../__internal/sample_count.hpp"

#include <integer.hpp>

namespace vk {

	struct pipeline_multisample_state_create_info {
		const uint32     structure_type = 24;
		const void*      next;
		uint32           flags;
		vk::sample_count rasterization_samples{ 1 };
		uint32           enable_sample_shading;
		float            min_sample_shading{ 1.0 };
		const uint32*    sample_mask;
		uint32           enable_alpha_to_coverage;
		uint32           enable_alpha_to_one;
	};

} // vk