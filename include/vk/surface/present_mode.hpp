#pragma once

namespace vk {

	enum class present_mode {
		immediate                 = 0,
		mailbox                   = 1,
		fifo                      = 2,
		fifo_relaxed              = 3,
		shared_demand_refresh     = 1000111000,
		shared_continuous_refresh = 1000111001,
	};

} // vk