#pragma once

#include <core/type/range.hpp>
#include <core/elements/one_of.hpp>
#include <core/array.hpp>

#include "submit_info.hpp"
#include "present_info.hpp"
#include "../shared/result.hpp"
#include "../fence/handle.hpp"

namespace vk {
	struct queue {
		void* handle;

		vk::result try_submit(type::range_of_value_type<vk::submit_info> auto&& submits, vk::fence fence = { VK_NULL_HANDLE }) const {
			return vk::result {
				(uint32)vkQueueSubmit(
					(VkQueue) handle,
					(uint32) submits.size(),
					(VkSubmitInfo*) submits.data(),
					(VkFence) fence.handle
				)
			};
		}

		vk::result try_submit(vk::submit_info submit, vk::fence fence = { VK_NULL_HANDLE }) const {
			return try_submit(array{ submit }, fence);
		}

		void submit(vk::submit_info submit, vk::fence fence = { VK_NULL_HANDLE }) const {
			vk::result result = try_submit(submit, fence);
			if(!result.success()) throw result;
		}

		vk::result try_present(vk::present_info present_info) const {
			return {
				(uint32) vkQueuePresentKHR(
					(VkQueue) handle,
					(VkPresentInfoKHR*) &present_info
				)
			};
		}

		void present(vk::present_info present_info) const {
			vk::result result { try_present(present_info) };
			if(!result.success()) throw result;
		}
	};
}