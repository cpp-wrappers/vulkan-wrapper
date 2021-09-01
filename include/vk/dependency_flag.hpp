#pragma once

#include "headers.hpp"

namespace vk {

enum class dependency_flag {
	by_region = VK_DEPENDENCY_BY_REGION_BIT,
	device_group = VK_DEPENDENCY_DEVICE_GROUP_BIT,
	view_local = VK_DEPENDENCY_VIEW_LOCAL_BIT
};

}