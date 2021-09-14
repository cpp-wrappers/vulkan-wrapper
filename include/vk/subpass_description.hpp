#pragma once

#include "core/types.hpp"
#include "headers.hpp"
#include <core/flag_enum.hpp>
#include <core/named.hpp>
#include <core/storage.hpp>
#include <core/tuple.hpp>
#include "pipeline/bind_point.hpp"
#include "attachment_reference.hpp"

namespace vk {

enum class subpass_description_flag {
	per_view_attributes = VK_SUBPASS_DESCRIPTION_PER_VIEW_ATTRIBUTES_BIT_NVX,
	per_view_position_x_only = VK_SUBPASS_DESCRIPTION_PER_VIEW_POSITION_X_ONLY_BIT_NVX,
	fragment_region = VK_SUBPASS_DESCRIPTION_FRAGMENT_REGION_BIT_QCOM,
	shader_resolve = VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM
};

struct input_attachment_count : named<uint32_t> {};
struct input_attachments : named<const vk::attachment_reference*> {};
struct color_attachment_count : named<uint32_t> {};
struct color_attachments : named<const vk::attachment_reference*> {};
struct resolve_attachments : named<const vk::attachment_reference*> {};
struct depth_stencil_attachments : named<const vk::attachment_reference*> {};
struct preserve_attachment_count : named<uint32_t> {};
struct preserve_attachments : named<const uint32_t*> {};

struct subpass_description {
	flag_enum<vk::subpass_description_flag> flags{};
	vk::pipeline_bind_point pipeline_bind_point{ vk::pipeline_bind_point::graphics };
	vk::input_attachment_count input_attachment_count{ 0 };
	vk::input_attachments input_attachments{ nullptr };
	vk::color_attachment_count color_attachment_count{ 0 };
	vk::color_attachments color_attachments{ 0 };
	vk::resolve_attachments resolve_attachments{ nullptr };
	vk::depth_stencil_attachments depth_stencil_attachments{ nullptr };
	vk::preserve_attachment_count preserve_attachment_count{ 0 };
	vk::preserve_attachments preserve_attachments{ nullptr };

	template<typename... Args>
	struct construction_requirements {
		using Types = types::of<Args...>;

		template<typename T>
		static constexpr std::size_t count = Types::template count_of_same_as_type<T>;

		template<typename T>
		static constexpr bool has = count<T> == 1;

		static constexpr bool value =
			(has<vk::input_attachment_count> == has<vk::input_attachments>) &&
			(has<vk::color_attachment_count> == has<vk::color_attachments>) &&
			(
				!has<vk::resolve_attachments> ||
				has<vk::resolve_attachments> && has<vk::color_attachment_count>
			) &&
			count<vk::depth_stencil_attachments> <= 1 &&
			(has<vk::preserve_attachment_count> == has<vk::preserve_attachments>) &&
			Types::template erase_same_as_one_of_types<
				vk::subpass_description_flag, vk::pipeline_bind_point, vk::input_attachment_count,
				vk::input_attachments, vk::color_attachment_count, vk::color_attachments,
				vk::resolve_attachments, vk::depth_stencil_attachments,
				vk::preserve_attachment_count, vk::preserve_attachments
			>::empty
		;
	};

	template<typename... Args>
	requires(construction_requirements<Args...>::value)
	subpass_description(Args... args) {
		using Types = types::of<Args...>;

		tuple{ args... }
			.get([&](vk::subpass_description_flag f) { flags.set(f); })
			.get([&](vk::input_attachment_count iac) { input_attachment_count = iac; })
			.get([&](vk::input_attachments ia) { input_attachments = ia; })
			.get([&](vk::color_attachment_count iac) { color_attachment_count = iac; })
			.get([&](vk::color_attachments ia) { color_attachments = ia; })
			.get([&](vk::resolve_attachments ra) { resolve_attachments = ra; })
			.get([&](vk::resolve_attachments ra) { resolve_attachments = ra; })
			.get([&](vk::depth_stencil_attachments dsa) { depth_stencil_attachments = dsa; })
			.get([&](vk::preserve_attachment_count pac) { preserve_attachment_count = pac; })
			.get([&](vk::preserve_attachments pa) { preserve_attachments = pa; })
		;
	}
};

}

static_assert(sizeof(vk::subpass_description) == sizeof(VkSubpassDescription));