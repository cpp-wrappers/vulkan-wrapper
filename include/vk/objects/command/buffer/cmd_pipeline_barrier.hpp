#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/are_contain_one_type.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/elements/range_of_value_type.hpp>

#include "../../../shared/dependency.hpp"
#include "../../../elements/possibly_guarded_handle_of.hpp"
#include "../../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../pipeline/stage.hpp"
#include "image_memory_barrier.hpp"
#include "handle.hpp"

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_contain_one_type<vk::src_stages>::decay,
		types::are_contain_one_type<vk::dst_stages>::decay,
		types::are_contain_one_type<vk::dependencies>::decay,
		types::count_of_ranges_of_value_type<vk::image_memory_barrier>::less_or_equals<1>
	>::for_types_of<Args...>
	void cmd_pipeline_barrier(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>::for_elements_of(args...);
		vk::src_stages src_stages = elements::of_type<vk::src_stages>::ignore_const::ignore_reference::for_elements_of(args...);
		vk::dst_stages dst_stages = elements::of_type<vk::dst_stages>::ignore_const::ignore_reference::for_elements_of(args...);
		vk::dependencies dependencies = elements::of_type<vk::dependencies>::ignore_const::ignore_reference::for_elements_of(args...);

		auto& image_barriers = elements::range_of_value_type<vk::image_memory_barrier>::for_elements_of<Args...>(args...);

		vkCmdPipelineBarrier(
			(VkCommandBuffer) vk::get_handle_value(command_buffer),
			(VkPipelineStageFlags) src_stages.value,
			(VkPipelineStageFlags) dst_stages.value,
			(VkDependencyFlags) dependencies.value,
			0,
			nullptr,
			0,
			nullptr,
			(uint32) image_barriers.size(),
			(VkImageMemoryBarrier*) image_barriers.data()
		);
	}

} // vk