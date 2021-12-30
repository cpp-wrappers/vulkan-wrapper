#pragma once

#include <core/array.hpp>
#include <core/elements/for_each_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>

#include "../../image/memory_barrier.hpp"
#include "../../pipeline/stage.hpp"
#include "../../pipeline/graphics/handle.hpp"
#include "../../shared/result.hpp"
#include "../../shared/dependency.hpp"
#include "../../shared/guarded_handle.hpp"
#include "../../shared/viewport.hpp"
#include "../../shared/handle.hpp"
#include "../../buffer/handle.hpp"
#include "../../shared/device_size.hpp"
#include "../../shared/extent.hpp"
#include "../../shared/rect2d.hpp"
#include "clear.hpp"
#include "begin_info.hpp"

namespace vk {

	struct src_stage_flags : flag_enum<vk::pipeline_stage> {};
	struct dst_stage_flags : flag_enum<vk::pipeline_stage> {};

	struct command_buffer;

	template<>
	constexpr inline bool is_allocatable<vk::command_buffer> = true;

	template<>
	struct vk::handle<vk::command_buffer> : vk::handle_base<vk::dispatchable> {

		template<typename... Args> vk::result try_begin(Args&&... args) const;
		template<typename... Args> void begin(Args&&... args) const;

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::count_of_type<vk::src_stage_flags>::equals<1>,
				types::count_of_type<vk::dst_stage_flags>::equals<1>,
				types::count_of_type<vk::dependency_flags>::equals<1>,
				types::count_of_ranges_of_value_type<vk::image_memory_barrier>::greater_or_equals<0>
			>::for_types_of<Args...>
		)
		void cmd_pipeline_barrier(Args... args) const {
			auto& image_barriers = elements::range_of_value_type<vk::image_memory_barrier>::for_elements_of<Args...>(args...);

			vkCmdPipelineBarrier(
				(VkCommandBuffer) vk::get_handle_value(*this),
				(VkPipelineStageFlags) elements::of_type<vk::src_stage_flags&>::for_elements_of(args...).value,
				(VkPipelineStageFlags) elements::of_type<vk::dst_stage_flags&>::for_elements_of(args...).value,
				(VkDependencyFlags) elements::of_type<vk::dependency_flags&>::for_elements_of(args...).value,
				0,
				nullptr,
				0,
				nullptr,
				(uint32) image_barriers.size(),
				(VkImageMemoryBarrier*) image_barriers.data()
			);
		}

		void cmd_clear_color_image(
			vk::handle<vk::image> image,
			vk::image_layout layout,
			vk::clear_color_value clear_color,
			range::of_value_type<vk::image_subresource_range> auto&& ranges
		) const {
			vkCmdClearColorImage(
				(VkCommandBuffer) vk::get_handle_value(*this),
				(VkImage) image.value,
				(VkImageLayout) layout,
				(VkClearColorValue*) &clear_color,
				(uint32) ranges.size(),
				(VkImageSubresourceRange*) ranges.data()
			);
		}

		vk::result try_end() const {
			return {
				(int32) vkEndCommandBuffer((VkCommandBuffer) vk::get_handle_value(*this))
			};
		}

		void end() const {
			vk::result result = try_end();
			if(!result.success()) throw result;
		}

		template<typename... Args> void cmd_begin_render_pass(Args&&... args) const;

		void cmd_bind_pipeline(vk::ordinary_or_guarded_handle<vk::graphics_pipeline> auto& pipeline) const {
			vkCmdBindPipeline(
				(VkCommandBuffer) vk::get_handle_value(*this),
				VK_PIPELINE_BIND_POINT_GRAPHICS,
				(VkPipeline) vk::get_handle_value(pipeline)
			);
		}

		void cmd_set_viewport(vk::viewport viewport) const {
			vkCmdSetViewport(
				(VkCommandBuffer) vk::get_handle_value(*this),
				0,
				1,
				(VkViewport*) &viewport
			);
		}

		void cmd_set_viewport(vk::extent<2> viewport) const {
			return cmd_set_viewport(vk::viewport {
				.width = (float)viewport.width(),
				.height = (float)viewport.height()
			});
		}

		void cmd_set_scissor(vk::rect2d scissor) const {
			vkCmdSetScissor(
				(VkCommandBuffer) vk::get_handle_value(*this),
				0,
				1,
				(VkRect2D*) &scissor
			);
		}

		void cmd_set_scissor(vk::extent<2> scissor) const {
			cmd_set_scissor(vk::rect2d {
				vk::offset<2>{ 0, 0 },
				scissor
			});
		}

		template<typename... Args> void cmd_draw(Args&&... args) const;

		void cmd_end_render_pass() const {
			vkCmdEndRenderPass((VkCommandBuffer) vk::get_handle_value(*this));
		}

		template<typename... Args> void cmd_bind_vertex_buffers(Args&&... args) const;
		template<typename... Args> void cmd_bind_vertex_buffer(Args&&... args) const;
	};

} // vk

#include "begin.hpp"

template<typename... Args>
vk::result vk::handle<vk::command_buffer>::try_begin(Args&&... args) const {
	return vk::try_begin_command_buffer(*this, forward<Args>(args)...);
}

template<typename... Args>
void vk::handle<vk::command_buffer>::begin(Args&&... args) const {
	vk::begin_command_buffer(*this, forward<Args>(args)...);
}

#include "cmd_begin_render_pass.hpp"

template<typename... Args>
void vk::handle<vk::command_buffer>::cmd_begin_render_pass(Args&&... args) const {
	vk::cmd_begin_render_pass(*this, forward<Args>(args)...);
}

#include "cmd_draw.hpp"

template<typename... Args>
void vk::handle<vk::command_buffer>::cmd_draw(Args&&... args) const {
	vk::cmd_draw(*this, forward<Args>(args)...);
}

#include "cmd_bind_vertex_buffers.hpp"

template<typename... Args> 
void vk::handle<vk::command_buffer>::cmd_bind_vertex_buffers(Args&&... args) const {
	vk::cmd_bind_vertex_buffers(*this, forward<Args>(args)...);
}

#include "cmd_bind_vertex_buffer.hpp"

template<typename... Args> 
void vk::handle<vk::command_buffer>::cmd_bind_vertex_buffer(Args&&... args) const {
	vk::cmd_bind_vertex_buffer(*this, forward<Args>(args)...);
}