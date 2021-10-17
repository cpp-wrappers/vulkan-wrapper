#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/types/are_contain_range_of_value_type.hpp>

#include "../attachment_description.hpp"
#include "../result.hpp"
#include "create_info.hpp"

namespace vk {

	struct device;
	struct render_pass;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_ranges_of_value_type<vk::subpass_description>::less_or_equals<1u>,
			types::count_of_ranges_of_value_type<vk::subpass_dependency>::greater_or_equals<0u>,
			types::count_of_ranges_of_value_type<vk::attachment_description>::greater_or_equals<0u>,
			types::count_of_type<vk::device&>::equals<1u>
		>::for_types_of<Args...>
	)
	vk::render_pass& create_render_pass(Args&&... args) {
		using Types = types::of<Args...>;

		vk::render_pass_create_info ci{};

		auto& subpass_descriptions = elements::range_of_value_type<vk::subpass_description>::for_elements_of(args...);
		ci.subpass_count = (primitive::uint32)(primitive::uint) subpass_descriptions.size();
		ci.subpasses = subpass_descriptions.data();

		if constexpr(types::are_contain_range_of_value_type<vk::subpass_dependency>::for_types_of<Args...>) {
			auto& subpass_dependencies = elements::range_of_value_type<vk::subpass_dependency>::for_elements_of(args...);
			ci.dependency_count = (primitive::uint32)(primitive::uint) subpass_dependencies.size();
			ci.dependencies = subpass_dependencies.data();
		}

		if constexpr(types::are_contain_range_of_value_type<vk::attachment_description>::for_types_of<Args...>) {
			auto& attachment_descriptions = elements::range_of_value_type<vk::attachment_description>::for_elements_of(args...);
			ci.attachment_count = (primitive::uint32)(primitive::uint) attachment_descriptions.size();
			ci.attachments = attachment_descriptions.data();
		}
		
		vk::render_pass* render_pass;

		vk::throw_if_error(
			vkCreateRenderPass(
				(VkDevice) & elements::of_type<vk::device&>::for_elements_of(args...),
				(VkRenderPassCreateInfo*) &ci,
				nullptr,
				(VkRenderPass*) &render_pass
			)
		);

		return *render_pass;
	}
}