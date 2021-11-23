#pragma once

#include <core/integer.hpp>
#include <core/type/range.hpp>

#include "shared/headers.hpp"
#include "queue/submit_info.hpp"
#include "swapchain/present_info.hpp"
#include "shared/result.hpp"

namespace vk {

	class semaphore;

	struct queue {
		queue(const queue&) = delete;

		vk::result try_submit(type::range_of_value_type<vk::submit_info> auto&& submit_infos) const {
			return vk::result {
				(uint32) vkQueueSubmit(
					(VkQueue) this,
					(uint32) submit_infos.size(),
					(VkSubmitInfo*) submit_infos.data(),
					nullptr
				)
			};
		}

		vk::result try_present() const {
			
		}
	};
}