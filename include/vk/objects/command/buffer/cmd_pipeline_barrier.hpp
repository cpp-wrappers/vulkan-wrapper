#pragma once

#include "handle.hpp"
#include "image_memory_barrier.hpp"
#include "../../pipeline/stage.hpp"
#include "../../../types/are_contain_one_possibly_guarded_handle_of.hpp"
#include "../../../elements/possibly_guarded_handle_of.hpp"
#include "../../../shared/dependency.hpp"

#include <core/range/of_value_type.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>

namespace vk {

	template<typename... Args>
	requires types::are_exclusively_satsify_predicates<
		types::vk::are_contain_one_possibly_guarded_handle_of<vk::command_buffer>,
		types::are_contain_one_decayed_same_as<vk::src_stages>,
		types::are_contain_one_decayed_same_as<vk::dst_stages>,
		types::are_may_contain_one_decayed_same_as<vk::dependencies>,
		types::count_of_ranges_of_value_type<vk::image_memory_barrier>::less_or_equals<1>
	>::for_types<Args...>
	void cmd_pipeline_barrier(Args&&... args) {
		auto& command_buffer = elements::vk::possibly_guarded_handle_of<vk::command_buffer>(args...);
		vk::src_stages src_stages = elements::decayed_same_as<vk::src_stages>(args...);
		vk::dst_stages dst_stages = elements::decayed_same_as<vk::dst_stages>(args...);
		vk::dependencies dependencies{};
		
		if constexpr(types::are_contain_decayed_same_as<vk::dependencies>::for_types<Args...>) {
			dependencies = elements::decayed_same_as<vk::dependencies>(args...);
		}

		auto& image_barriers = elements::range_of_value_type<vk::image_memory_barrier>(args...);

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

template<typename... Args>
auto& vk::handle<vk::command_buffer>::cmd_pipeline_barrier(Args&&... args) const {
	vk::cmd_pipeline_barrier(*this, forward<Args>(args)...); return *this;
}