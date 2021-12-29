#pragma once

#include "../device/handle.hpp"
#include "../shared/create_or_allocate.hpp"
#include "handle.hpp"
#include "attachment_description.hpp"
#include "create_info.hpp"

namespace vk {

	template<>
	struct vk::try_create_t<vk::render_pass> {

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::vk::contain_one<vk::device>,
				types::count_of_ranges_of_value_type<vk::subpass_description>::equals<1>,
				types::count_of_ranges_of_value_type<vk::subpass_dependency>::less_or_equals<1>,
				types::count_of_ranges_of_value_type<vk::attachment_description>::less_or_equals<1>
			>::for_types_of<Args...>
		)
		elements::one_of<vk::result, vk::handle<vk::render_pass>>
		operator () (Args&&... args) const {
			vk::render_pass_create_info ci{};

			auto& subpass_descriptions = elements::range_of_value_type<vk::subpass_description>::for_elements_of(args...);
			ci.subpass_count = (uint32) subpass_descriptions.size();
			ci.subpasses = subpass_descriptions.data();

			if constexpr(types::are_contain_range_of_value_type<vk::subpass_dependency>::for_types_of<Args...>) {
				auto& subpass_dependencies = elements::range_of_value_type<vk::subpass_dependency>::for_elements_of(args...);
				ci.dependency_count = (uint32) subpass_dependencies.size();
				ci.dependencies = subpass_dependencies.data();
			}

			if constexpr(types::are_contain_range_of_value_type<vk::attachment_description>::for_types_of<Args...>) {
				auto& attachment_descriptions = elements::range_of_value_type<vk::attachment_description>::for_elements_of(args...);
				ci.attachment_count = (uint32) attachment_descriptions.size();
				ci.attachments = attachment_descriptions.data();
			}

			auto& device = elements::vk::of_type<vk::device>::for_elements_of(args...);

			VkRenderPass render_pass;

			vk::result result {
				(int32) vkCreateRenderPass(
					(VkDevice) vk::get_handle_value(device),
					(VkRenderPassCreateInfo*) &ci,
					nullptr,
					(VkRenderPass*) &render_pass
				)
			};

			if(result.success()) return vk::handle<vk::render_pass>{ render_pass };

			return result;
		}
	};

}