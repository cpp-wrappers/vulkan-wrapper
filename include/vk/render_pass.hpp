#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_ranges_of_value_type.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/range_of_value_type.hpp>
#include <core/types/are_contain_range_of_value_type.hpp>
#include <core/elements/one_of.hpp>

#include "shared/attachment_description.hpp"
#include "shared/result.hpp"
#include "render_pass/create_info.hpp"

namespace vk {
	class device;

	class render_pass {
		void* m_render_pass;
		const device& m_device;
		
	public:
		render_pass(const render_pass&) = delete;
		render_pass(render_pass&& other) : m_render_pass{ other.m_render_pass }, m_device{ other.m_device } { other.m_render_pass = nullptr; }
		render_pass(VkRenderPass render_pass, const vk::device& device) : m_render_pass{ render_pass }, m_device{ device } {}


		~render_pass() {
			if(m_render_pass) {
				vkDestroyRenderPass(
					*(VkDevice*) & m_device,
					(VkRenderPass) m_render_pass,
					nullptr
				);

				m_render_pass = nullptr;
			}
		}
	};

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_ranges_of_value_type<vk::subpass_description>::less_or_equals<1u>,
			types::count_of_ranges_of_value_type<vk::subpass_dependency>::greater_or_equals<0u>,
			types::count_of_ranges_of_value_type<vk::attachment_description>::greater_or_equals<0u>,
			types::count_of_type<vk::device&>::equals<1u>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::render_pass>
	try_create_render_pass(Args&&... args) {
		using Types = types::of<Args...>;

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
		
		const vk::device& device = elements::of_type<vk::device&>::for_elements_of(args...);
		VkRenderPass render_pass;

		vk::result result {
			(uint32) vkCreateRenderPass(
				*(VkDevice*) &device,
				(VkRenderPassCreateInfo*) &ci,
				nullptr,
				(VkRenderPass*) &render_pass
			)
		};
		if(!result.success()) return result;

		return vk::render_pass{ render_pass, device };
	}

	template<typename... Args>
	vk::render_pass create_render_pass(Args&&... args) {
		return try_create_render_pass(forward<Args>(args)...).template move<vk::render_pass>();
	}

}