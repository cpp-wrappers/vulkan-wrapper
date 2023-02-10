#pragma once

#include "./handle.hpp"
#include "./memory_barrier.hpp"
#include "./buffer_memory_barrier.hpp"
#include "./image_memory_barrier.hpp"
#include "../__internal/function.hpp"
#include "../__internal/dependency.hpp"
#include "../__pipeline/stage.hpp"
#include "../__instance/handle.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct cmd_pipeline_barrier_function : vk::function<void(*)(
		handle<vk::command_buffer>::underlying_type command_buffer,
		vk::src_stages src_stage_mask,
		vk::dst_stages dst_stage_mask,
		vk::dependencies dependency_flags,
		uint32 memory_barrier_count,
		const vk::memory_barrier* memory_barriers,
		uint32 buffer_memory_barrier_count,
		const vk::buffer_memory_barrier* buffer_memory_barriers,
		uint32 image_memory_barrier_count,
		const vk::image_memory_barrier* image_memory_barriers
	)> {
		static constexpr auto name = "vkCmdPipelineBarrier";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<handle<vk::command_buffer>> == 1,
		count_of_decayed_same_as<vk::src_stages> == 1,
		count_of_decayed_same_as<vk::dst_stages> == 1,
		count_of_decayed_same_as<vk::dependencies> <= 1,
		count_of_range_of_decayed<vk::memory_barrier> <= 1,
		count_of_range_of_decayed<vk::buffer_memory_barrier> <= 1,
		count_of_range_of_decayed<vk::image_memory_barrier> <= 1
	>
	void cmd_pipeline_barrier(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = a.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::command_buffer> command_buffer = a.template
			get_decayed_same_as<handle<vk::command_buffer>>();

		vk::src_stages src_stages = a.template
			get_decayed_same_as<vk::src_stages>();

		vk::dst_stages dst_stages = a.template
			get_decayed_same_as<vk::dst_stages>();

		vk::dependencies dependencies{};
		
		if constexpr (types<Args...>::template
			count_of_decayed_same_as<vk::dependencies> > 0
		) {
			dependencies = a.template
				get_decayed_same_as<vk::dependencies>();
		}

		uint32 memory_barrier_count{};
		const vk::memory_barrier* memory_barriers{};

		if constexpr(types<Args...>::template
			count_of_range_of_decayed<vk::memory_barrier> > 0
		) {
			auto& memory_barriers0 = a.template
				get_range_of_decayed<vk::memory_barrier>();
			memory_barrier_count = (uint32) memory_barriers0.size();
			memory_barriers = memory_barriers0.iterator();
		}

		uint32 buffer_barrier_count{};
		const vk::buffer_memory_barrier* buffer_barriers{};

		if constexpr(types<Args...>::template
			count_of_range_of_decayed<vk::buffer_memory_barrier> > 0
		) {
			auto& buffer_barriers0 = a.template
				get_range_of_decayed<vk::buffer_memory_barrier>();
			buffer_barrier_count = (uint32) buffer_barriers0.size();
			buffer_barriers = buffer_barriers0.iterator();
		}

		uint32 image_barrier_count{};
		const vk::image_memory_barrier* image_barriers{};

		if constexpr(types<Args...>::template
			count_of_range_of_decayed<vk::image_memory_barrier> > 0
		) {
			auto& image_barriers0 = a.template
				get_range_of_decayed<vk::image_memory_barrier>();
			image_barrier_count = (uint32) image_barriers0.size();
			image_barriers = image_barriers0.iterator();
		}

		vk::get_device_function<vk::cmd_pipeline_barrier_function>(
			instance, device
		)(
			command_buffer.underlying(),
			src_stages,
			dst_stages,
			dependencies,
			memory_barrier_count,
			memory_barriers,
			buffer_barrier_count,
			buffer_barriers,
			image_barrier_count,
			image_barriers
		);
	} // cmd_pipeline_barrier

} // vk