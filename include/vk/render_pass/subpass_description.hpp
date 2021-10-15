#pragma once

#include <core/flag_enum.hpp>
#include <core/storage.hpp>
#include <core/integer.hpp>
#include <core/pointer.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/types/are_contain_type.hpp>

#include "../headers.hpp"
#include "../pipeline/bind_point.hpp"
#include "../attachment_reference.hpp"

namespace vk {

enum class subpass_description_flag {
	per_view_attributes = VK_SUBPASS_DESCRIPTION_PER_VIEW_ATTRIBUTES_BIT_NVX,
	per_view_position_x_only = VK_SUBPASS_DESCRIPTION_PER_VIEW_POSITION_X_ONLY_BIT_NVX,
	fragment_region = VK_SUBPASS_DESCRIPTION_FRAGMENT_REGION_BIT_QCOM,
	shader_resolve = VK_SUBPASS_DESCRIPTION_SHADER_RESOLVE_BIT_QCOM
};

struct input_attachment_count : uint32 {};
struct input_attachments : pointer_of<const vk::attachment_reference> {};
struct color_attachment_count : uint32 {};
struct color_attachments : pointer_of<const vk::attachment_reference> {};
struct resolve_attachments : pointer_of<const vk::attachment_reference> {};
struct depth_stencil_attachments : pointer_of<const vk::attachment_reference> {};
struct preserve_attachment_count : uint32 {};
struct preserve_attachments : pointer_of<const uint32> {};

struct subpass_description {
	flag_enum<vk::subpass_description_flag> flags{};
	vk::pipeline_bind_point pipeline_bind_point{ vk::pipeline_bind_point::graphics };
	vk::input_attachment_count input_attachment_count{};
	vk::input_attachments input_attachments{};
	vk::color_attachment_count color_attachment_count{};
	vk::color_attachments color_attachments{};
	vk::resolve_attachments resolve_attachments{};
	vk::depth_stencil_attachments depth_stencil_attachments{};
	vk::preserve_attachment_count preserve_attachment_count{};
	vk::preserve_attachments preserve_attachments{};

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::input_attachment_count>::greater_or_equals<0u>,
			types::count_of_type<vk::input_attachments>::less_or_equals<1u>,
			types::count_of_type<vk::color_attachment_count>::greater_or_equals<0u>,
			types::count_of_type<vk::color_attachments>::less_or_equals<1u>,
			types::count_of_type<vk::resolve_attachments>::less_or_equals<1u>,
			types::count_of_type<vk::depth_stencil_attachments>::less_or_equals<1u>,
			types::count_of_type<vk::preserve_attachment_count>::less_or_equals<1u>,
			types::count_of_type<vk::preserve_attachments>::less_or_equals<1u>
		>::for_types_of<Args...> &&
		(types::are_contain_type<vk::input_attachment_count>::for_types_of<Args...> == types::are_contain_type<vk::input_attachments>::for_types_of<Args...>) &&
		(types::are_contain_type<vk::color_attachment_count>::for_types_of<Args...> == types::are_contain_type<vk::color_attachments>::for_types_of<Args...>) &&
		(
			!types::are_contain_type<vk::resolve_attachments>::for_types_of<Args...> ||
			types::are_contain_type<vk::resolve_attachments>::for_types_of<Args...> && types::are_contain_type<vk::color_attachment_count>::for_types_of<Args...>
		) &&
		types::count_of_type<vk::depth_stencil_attachments>::for_types_of<Args...> <= 1u &&
		(types::are_contain_type<vk::preserve_attachment_count>::for_types_of<Args...> == types::are_contain_type<vk::preserve_attachments>::for_types_of<Args...>)
	)
	subpass_description(Args... args) {
		using Types = types::of<Args...>;

		if constexpr(types::are_contain_type<vk::input_attachment_count>::for_types_of<Args...>)
			input_attachment_count = elements::of_type<vk::input_attachment_count&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::input_attachments>::for_types_of<Args...>)
			input_attachments = elements::of_type<vk::input_attachments&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::color_attachment_count>::for_types_of<Args...>)
			color_attachment_count = elements::of_type<vk::color_attachment_count&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::color_attachments>::for_types_of<Args...>)
			color_attachments = elements::of_type<vk::color_attachments&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::resolve_attachments>::for_types_of<Args...>)
			resolve_attachments = elements::of_type<vk::resolve_attachments&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::depth_stencil_attachments>::for_types_of<Args...>)
			depth_stencil_attachments = elements::of_type<vk::depth_stencil_attachments&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::preserve_attachment_count>::for_types_of<Args...>)
			preserve_attachment_count = elements::of_type<vk::preserve_attachment_count&>::for_elements_of(args...);

		if constexpr(types::are_contain_type<vk::preserve_attachments>::for_types_of<Args...>)
			preserve_attachments = elements::of_type<vk::preserve_attachments&>::for_elements_of(args...);
	}
};

}

static_assert(sizeof(vk::subpass_description) == sizeof(VkSubpassDescription));