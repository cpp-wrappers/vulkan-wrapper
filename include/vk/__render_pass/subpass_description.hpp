#pragma once

#include <enum_flags.hpp>
#include <array.hpp>
#include <types.hpp>
#include <tuple.hpp>
#include <range.hpp>

#include "./attachment_reference.hpp"
#include "../__pipeline/bind_point.hpp"

namespace vk {

	enum class subpass_description_flag {
		per_view_attributes      = 0x00000001,
		per_view_position_x_only = 0x00000002,
		fragment_region          = 0x00000004,
		shader_resolve           = 0x00000008
	};

	struct input_attachment_reference : attachment_reference {};
	struct color_attachment_reference : attachment_reference {};
	struct resolve_attachment_reference : attachment_reference {};
	struct depth_stencil_attachment_reference : attachment_reference {};
	struct preserve_attachment_reference : attachment_reference {};

	struct _subpass_description {
		enum_flags<vk::subpass_description_flag> flags{};
		vk::pipeline_bind_point pipeline_bind_point
			= vk::pipeline_bind_point::graphics;
		uint32 input_attachment_count = 0;
		const vk::input_attachment_reference*
			input_attachments = nullptr;
		uint32 color_attachment_count = 0;
		const vk::color_attachment_reference*
			color_attachments = nullptr;
		const vk::resolve_attachment_reference*
			resolve_attachments = nullptr;
		const vk::depth_stencil_attachment_reference*
			depth_stencil_attachments = nullptr;
		uint32 preserve_attachment_count = 0;
		const vk::preserve_attachment_reference*
			preserve_attachments = nullptr;
	};

	struct _subpass_description_mark{};

	inline constexpr auto is_subpass_description
		= is_derived_from<_subpass_description_mark>;

	template<
		basic_range InputAttachements,
		basic_range ColorAttachements,
		basic_range ResolveAttachements,
		basic_range DepthStencilAttachements,
		basic_range PreserveAttachements
	>
	struct subpass_description : _subpass_description_mark {
		InputAttachements input_attachements;
		ColorAttachements color_attachements;
		ResolveAttachements resolve_attachements;
		DepthStencilAttachements depth_stencil_attachements;
		PreserveAttachements preserve_attachements;
	
		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			is_same_as<InputAttachements> <= 1,
			is_same_as<ColorAttachements> <= 1,
			is_same_as<ResolveAttachements> <= 1,
			is_same_as<DepthStencilAttachements> <=1,
			is_same_as<PreserveAttachements> <= 1
		>
		subpass_description(Args&&... args) :
			input_attachements {
				tuple{ args... }.template get_or<
					is_same_as<decay<InputAttachements>>.decayed
				>([]{ return span<vk::input_attachment_reference>{}; })
			},
			color_attachements {
				tuple{ args... }.template get_or<
					is_same_as<decay<ColorAttachements>>.decayed
				>([]{ return span<vk::color_attachment_reference>{}; })
			},
			resolve_attachements {
				tuple{ args... }.template get_or<
					is_same_as<decay<ResolveAttachements>>.decayed
				>([]{ return span<vk::resolve_attachment_reference>{}; })
			},
			depth_stencil_attachements {
				tuple{ args... }.template get_or<
					is_same_as<decay<DepthStencilAttachements>>.decayed
				>([]{ return span<vk::depth_stencil_attachment_reference>{}; })
			},
			preserve_attachements {
				tuple{ args... }.template get_or<
					is_same_as<decay<PreserveAttachements>>.decayed
				>([]{ return span<vk::preserve_attachment_reference>{}; })
			}
		{} // constructor

		operator vk::_subpass_description() & {
			return {
				.input_attachment_count = (uint32) input_attachements.size(),
				.input_attachments = input_attachements.iterator(),
				.color_attachment_count = (uint32) color_attachements.size(),
				.color_attachments = color_attachements.iterator(),
				.resolve_attachments = resolve_attachements.iterator(),
				.depth_stencil_attachments = depth_stencil_attachements.iterator(),
				.preserve_attachment_count = (uint32) preserve_attachements.size(),
				.preserve_attachments = preserve_attachements.iterator()
			};
		}

	}; // subpass_description

	template<typename... Args>
	subpass_description(Args&&... args) -> subpass_description<
		typename types<Args...>::template get_or<
			is_range_of<is_same_as<vk::input_attachment_reference>.decayed>,
			span<vk::input_attachment_reference>
		>,
		typename types<Args...>::template get_or<
			is_range_of<is_same_as<vk::color_attachment_reference>.decayed>,
			span<vk::color_attachment_reference>
		>,
		typename types<Args...>::template get_or<
			is_range_of<is_same_as<vk::resolve_attachment_reference>.decayed>,
			span<vk::resolve_attachment_reference>
		>,
		typename types<Args...>::template get_or<
			is_range_of<is_same_as<vk::depth_stencil_attachment_reference>.decayed>,
			span<vk::depth_stencil_attachment_reference>
		>,
		typename types<Args...>::template get_or<
			is_range_of<is_same_as<vk::preserve_attachment_reference>.decayed>,
			span<vk::preserve_attachment_reference>
		>
	>;

} // vk