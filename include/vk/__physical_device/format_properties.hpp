#pragma once

#include "./format_feature.hpp"

namespace vk {

	struct format_properties {
		vk::format_features linearTilingFeatures;
		vk::format_features optimalTilingFeatures;
		vk::format_features bufferFeatures;
	};

} // vk