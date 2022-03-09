#pragma once

#include "handle.hpp"
#include "attachment_description.hpp"
#include "create_info.hpp"

#include "vk/create_or_allocate.hpp"
#include "vk/device/handle.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::render_pass> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::count_of_ranges_of<vk::subpass_description>::equals<1>,
			types::count_of_ranges_of<vk::subpass_dependency>::less_or_equals<1>,
			types::count_of_ranges_of<vk::attachment_description>::less_or_equals<1>
		>::for_types<Args...>
		vk::expected<vk::handle<vk::render_pass>>
		operator () (Args&&... args) const {
			vk::render_pass_create_info ci{};

			auto& subpass_descriptions = elements::range_of<vk::subpass_description>(args...);
			ci.subpass_count = (uint32) subpass_descriptions.size();
			ci.subpasses = subpass_descriptions.data();

			if constexpr(types::are_contain_range_of<vk::subpass_dependency>::for_types<Args...>) {
				auto& subpass_dependencies = elements::range_of<vk::subpass_dependency>(args...);
				ci.dependency_count = (uint32) subpass_dependencies.size();
				ci.dependencies = subpass_dependencies.data();
			}

			if constexpr(types::are_contain_range_of<vk::attachment_description>::for_types<Args...>) {
				auto& attachment_descriptions = elements::range_of<vk::attachment_description>(args...);
				ci.attachment_count = (uint32) attachment_descriptions.size();
				ci.attachments = attachment_descriptions.data();
			}

			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>(args...);

			vk::handle<vk::render_pass> render_pass;

			vk::result result {
				(int32) vkCreateRenderPass(
					(VkDevice) vk::get_handle_value(device),
					(VkRenderPassCreateInfo*) &ci,
					(VkAllocationCallbacks*) nullptr,
					(VkRenderPass*) &render_pass
				)
			};

			if(result.error()) return result;

			return render_pass;
		}

	};

} // vk