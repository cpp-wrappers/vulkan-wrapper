#pragma once

namespace vk {

	enum class compare_op {
		never            = 0,
		less             = 1,
		equal            = 2,
		less_or_equal    = 3,
		greater          = 4,
		not_equal        = 5,
		greater_or_equal = 6,
		always           = 7
	};

} // vk