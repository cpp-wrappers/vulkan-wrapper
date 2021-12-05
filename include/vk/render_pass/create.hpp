#pragma once

#include "handle.hpp"

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/types/are_contain_range_of_value_type.hpp>
#include <core/elements/one_of.hpp>
#include <core/exchange.hpp>

#include "attachment_description.hpp"
#include "../shared/result.hpp"
#include "create_info.hpp"
#include "../device/handle.hpp"

namespace vk {
	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_ranges_of_value_type<vk::subpass_description>::equals<1>,
			types::count_of_ranges_of_value_type<vk::subpass_dependency>::less_or_equals<1>,
			types::count_of_ranges_of_value_type<vk::attachment_description>::less_or_equals<1>,
			types::count_of_type<vk::device>::equals<1>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::render_pass>
	try_create_render_pass(const Args&... args) {
		vk::render_pass_create_info ci{};

		auto& subpass_descriptions = elements::range_of_value_type<vk::subpass_description>::for_elements_of(args...);
		ci.subpass_count = (uint32) subpass_descriptions.size();
		ci.subpasses = subpass_descriptions.data();

		//if constexpr(types::are_contain_range_of_value_type<vk::subpass_dependency>::for_types_of<Args...>) {
			auto& subpass_dependencies = elements::range_of_value_type<vk::subpass_dependency>::for_elements_of(args...);
			ci.dependency_count = (uint32) subpass_dependencies.size();
			ci.dependencies = subpass_dependencies.data();
		//}

		//if constexpr(types::are_contain_range_of_value_type<vk::attachment_description>::for_types_of<Args...>) {
			auto& attachment_descriptions = elements::range_of_value_type<vk::attachment_description>::for_elements_of(args...);
			ci.attachment_count = (uint32) attachment_descriptions.size();
			ci.attachments = attachment_descriptions.data();
		//}
		
		vk::device device = elements::of_type<const vk::device&>::for_elements_of(args...);

		VkRenderPass render_pass;

		vk::result result {
			(int32) vkCreateRenderPass(
				(VkDevice) device.handle,
				(VkRenderPassCreateInfo*) &ci,
				nullptr,
				(VkRenderPass*) &render_pass
			)
		};
		
		if(result.success()) return vk::render_pass{ render_pass };

		return result;
	}

	template<typename... Args>
	vk::render_pass create_render_pass(Args&&... args) {
		auto result = try_create_render_pass(forward<Args>(args)...);
		if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
		return result.template get<vk::render_pass>();
	}
}