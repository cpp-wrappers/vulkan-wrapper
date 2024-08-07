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
		int /*vk::src_stages*/ src_stage_mask,
		int /*vk::dst_stages*/ dst_stage_mask,
		int /*vk::dependencies*/ dependency_flags,
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
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_same_as<handle<vk::command_buffer>>.decayed == 1,
		is_same_as<vk::src_stages>.decayed == 1,
		is_same_as<vk::dst_stages>.decayed == 1,
		is_same_as<vk::dependencies>.decayed <= 1,
		is_range_of<is_same_as<vk::memory_barrier>.decayed> <= 1,
		is_range_of<is_same_as<vk::buffer_memory_barrier>.decayed> <= 1,
		is_range_of<is_same_as<vk::image_memory_barrier>.decayed> <= 1
	>
	void cmd_pipeline_barrier(Args&&... args) {
		tuple a { args... };

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

		handle<vk::command_buffer> command_buffer = a.template
			get<is_same_as<handle<vk::command_buffer>>.decayed>();

		vk::src_stages src_stages = a.template
			get<is_same_as<vk::src_stages>.decayed>();

		vk::dst_stages dst_stages = a.template
			get<is_same_as<vk::dst_stages>.decayed>();

		vk::dependencies dependencies{};
		
		if constexpr (
			(is_same_as<vk::dependencies>.decayed > 0).for_types<Args...>()
		) {
			dependencies = a.template
				get<is_same_as<vk::dependencies>.decayed>();
		}

		uint32 memory_barrier_count{};
		const vk::memory_barrier* memory_barriers{};

		if constexpr(
			(is_range_of<is_same_as<vk::memory_barrier>.decayed> > 0)
			.for_types<Args...>()
		) {
			auto& memory_barriers0 = a.template
				get<is_range_of<is_same_as<vk::memory_barrier>.decayed>>();
			memory_barrier_count = (uint32) memory_barriers0.size();
			memory_barriers = memory_barriers0.iterator();
		}

		uint32 buffer_barrier_count{};
		const vk::buffer_memory_barrier* buffer_barriers{};

		if constexpr(
			(is_range_of<is_same_as<vk::buffer_memory_barrier>.decayed> > 0)
			.for_types<Args...>()
		) {
			auto& buffer_barriers0 = a.template
				get<is_range_of<is_same_as<vk::buffer_memory_barrier>.decayed>>();
			buffer_barrier_count = (uint32) buffer_barriers0.size();
			buffer_barriers = buffer_barriers0.iterator();
		}

		uint32 image_barrier_count{};
		const vk::image_memory_barrier* image_barriers{};

		if constexpr(
			(is_range_of<is_same_as<vk::image_memory_barrier>.decayed> > 0)
			.for_types<Args...>()
		) {
			auto& image_barriers0 = a.template
				get<is_range_of<is_same_as<vk::image_memory_barrier>.decayed>>();
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