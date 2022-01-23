#pragma once

#include "../headers.hpp"

namespace vk {

	enum class present_mode {
		immediate = VK_PRESENT_MODE_IMMEDIATE_KHR,
		mailbox = VK_PRESENT_MODE_MAILBOX_KHR,
		fifo = VK_PRESENT_MODE_FIFO_KHR,
		fifo_relaxed = VK_PRESENT_MODE_FIFO_RELAXED_KHR,
		shared_demand_refresh_khr = VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR,
		shared_continuous_refresh_khr = VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR,
	};

} // vk