#pragma once

#include "handle.hpp"
#include "image_memory_barrier.hpp"
#include "buffer_memory_barrier.hpp"

#include "../../pipeline/stage.hpp"
#include "../../dependency.hpp"

#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

extern "C" VK_ATTR void VK_CALL vkCmdPipelineBarrier(
	handle<vk::command_buffer> command_buffer,
	vk::src_stages src_stage_mask,
	vk::dst_stages dst_stage_mask,
	vk::dependencies dependency_flags,
	uint32 memory_barrier_count,
	const void*                      mamory_barriers,
	uint32 buffer_memory_barrier_count,
	const vk::buffer_memory_barrier* buffer_memory_barriers,
	uint32 image_memory_barrier_count,
	const vk::image_memory_barrier* image_memory_barriers
);

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satisfying_predicates<
		types::are_contain_one_decayed<handle<vk::command_buffer>>,
		types::are_contain_one_decayed<vk::src_stages>,
		types::are_contain_one_decayed<vk::dst_stages>,
		types::are_may_contain_one_decayed<vk::dependencies>,
		types::are_may_contain_range_of<vk::buffer_memory_barrier>,
		types::are_may_contain_range_of<vk::image_memory_barrier>
	>::for_types<Args...>
	void cmd_pipeline_barrier(Args&&... args) {
		auto command_buffer {
			elements::decayed<handle<vk::command_buffer>>(args...)
		};

		vk::src_stages src_stages = elements::decayed<vk::src_stages>(args...);
		vk::dst_stages dst_stages = elements::decayed<vk::dst_stages>(args...);
		vk::dependencies dependencies{};
		
		if constexpr (
			types::are_contain_decayed<vk::dependencies>::for_types<Args...>
		) { dependencies = elements::decayed<vk::dependencies>(args...); }

		uint32 buffer_barrier_count{};
		const vk::buffer_memory_barrier* buffer_barriers{};

		if constexpr(
			types::are_contain_range_of<
				vk::buffer_memory_barrier
			>::for_types<Args...>
		) {
			auto& buffer_barriers0 = elements::range_of<
				vk::buffer_memory_barrier
			>(args...);
			buffer_barrier_count = (uint32) buffer_barriers0.size();
			buffer_barriers = buffer_barriers0.data();
		}

		uint32 image_barrier_count{};
		const vk::image_memory_barrier* image_barriers{};

		if constexpr (
			types::are_contain_range_of<
				vk::image_memory_barrier
			>::for_types<Args...>
		) {
			auto& image_barriers0 = elements::range_of<
				vk::image_memory_barrier
			>(args...);
			image_barrier_count = (uint32) image_barriers0.size();
			image_barriers = image_barriers0.data();
		}

		vkCmdPipelineBarrier(
			command_buffer,
			src_stages,
			dst_stages,
			dependencies,
			0,
			nullptr,
			buffer_barrier_count,
			buffer_barriers,
			image_barrier_count,
			image_barriers
		);
	}

} // vk

template<typename... Args>
auto& handle<vk::command_buffer>::cmd_pipeline_barrier(Args&&... args) const {
	vk::cmd_pipeline_barrier(*this, forward<Args>(args)...); return *this;
}