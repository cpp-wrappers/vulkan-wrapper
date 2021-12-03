#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/types/first.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/for_each_of_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/array.hpp>

#include "begin_info.hpp"
#include "../../shared/result.hpp"
#include "../../pipeline/stage.hpp"
#include "../../shared/dependency.hpp"
#include "../../image/memory_barrier.hpp"
#include "clear.hpp"
#include "render_pass_begin_info.hpp"
#include "../../pipeline/handle.hpp"

namespace vk {

	struct src_stage_flags : flag_enum<vk::pipeline_stage> {};
	struct dst_stage_flags : flag_enum<vk::pipeline_stage> {};

	struct command_buffer {
		void* handle;

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::count_of_type<vk::command_buffer_usage>::greater_or_equals<0>,
				types::count_of_type<vk::render_pass>::equals<1>,
				types::count_of_type<vk::framebuffer>::equals<1>,
				types::count_of_type<vk::subpass>::equals<1>,
				types::count_of_type<vk::occlusion_query_enable>::less_or_equals<1>,
				types::count_of_type<vk::query_control>::greater_or_equals<0>,
				types::count_of_type<vk::query_pipeline_statistics>::greater_or_equals<0>
			>::for_types_of<Args...>
		)
		vk::result try_begin(Args... args) const {
			vk::command_buffer_inheritance_info ii {
				.render_pass = elements::of_type<vk::command_buffer>::for_elements_of<Args...>(args...),
				.subpass = elements::of_type<vk::subpass>::for_elements_of<Args...>(args...),
				.framebuffer = elements::of_type<vk::framebuffer>::for_elements_of<Args...>(args...),
				.occlusion_query_enable = elements::of_type<vk::occlusion_query_enable>::for_elements_of<Args...>(args...)
			};

			elements::for_each_of_type<vk::query_control>([&](auto f){ ii.query_flags.set(f); }, args...);
			elements::for_each_of_type<vk::query_pipeline_statistics>([&](auto f){ ii.pipeline_statistics.set(f); }, args...);

			vk::command_buffer_begin_info bi {
				.inheritance_info = &ii
			};

			elements::for_each_of_type<vk::command_buffer_usage>([&](auto f){ bi.usage.set(f); }, args...);

			return {
				(int32) vkBeginCommandBuffer(
					(VkCommandBuffer) handle,
					(VkCommandBufferBeginInfo*) &bi
				)
			};
		}

		template<typename... Args>
		requires(types::are_same::for_types_of<Args..., vk::command_buffer_usage>)
		vk::result try_begin(Args... args) const {
			vk::command_buffer_begin_info bi {
				.inheritance_info = nullptr
			};

			elements::for_each_of_type<vk::command_buffer_usage&>([&](auto f){ bi.usage.set(f); }, args...);

			return {
				(int32) vkBeginCommandBuffer(
					(VkCommandBuffer) handle,
					(VkCommandBufferBeginInfo*) &bi
				)
			};
		}

		void begin(auto... args) const {
			vk::result result = try_begin(args...);
			if(!result.success()) throw result;
		}

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
				(VkCommandBuffer) handle,
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
			vk::image image,
			vk::image_layout layout,
			vk::clear_color_value clear_color,
			type::range_of_value_type<vk::image_subresource_range> auto&& ranges
		) const {
			vkCmdClearColorImage(
				(VkCommandBuffer) handle,
				(VkImage) image.handle,
				(VkImageLayout) layout,
				(VkClearColorValue*) &clear_color,
				(uint32) ranges.size(),
				(VkImageSubresourceRange*) ranges.data()
			);
		}

		vk::result try_end() const {
			return {
				(int32) vkEndCommandBuffer((VkCommandBuffer) handle)
			};
		}

		void end() const {
			vk::result result = try_end();
			if(!result.success()) throw result;
		}

		void cmd_begin_render_pass(
			vk::render_pass_begin_info render_pass_begin_info
		) const {
			vkCmdBeginRenderPass(
				(VkCommandBuffer) handle,
				(VkRenderPassBeginInfo*) &render_pass_begin_info,
				VK_SUBPASS_CONTENTS_INLINE
			);
		}

		void cmd_bind_pipeline(
			vk::pipeline pipeline
		) const {
			vkCmdBindPipeline(
				(VkCommandBuffer) handle,
				VK_PIPELINE_BIND_POINT_GRAPHICS,
				(VkPipeline) pipeline.handle
			);
		}

		void cmd_draw(
			uint32 vertex_count,
			uint32 instance_count,
			uint32 first_vertex,
			uint32 first_instance
		) const {
			vkCmdDraw(
				(VkCommandBuffer) handle,
				vertex_count,
				instance_count,
				first_vertex,
				first_instance
			);
		}

		void cmd_end_render_pass() const {
			vkCmdEndRenderPass((VkCommandBuffer) handle);
		}

	};

} // vk