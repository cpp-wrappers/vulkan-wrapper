#pragma once

#include "./handle.hpp"
#include "./attachment_description.hpp"
#include "./create_info.hpp"
#include "../__internal/function.hpp"
#include "../__internal/result.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"

namespace vk {

	struct create_render_pass_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		const vk::render_pass_create_info* create_info,
		const void* allocator,
		handle<vk::render_pass>::underlying_type* render_pass
	)> {
		static constexpr auto name = "vkCreateRenderPass";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_range_of_decayed<vk::subpass_description> == 1,
		count_of_range_of_decayed<vk::subpass_dependency> <= 1,
		count_of_range_of_decayed<vk::attachment_description> <= 1
	>
	vk::expected<handle<vk::render_pass>>
	try_create_render_pass(Args&&... args) {
		vk::render_pass_create_info ci{};

		auto& subpass_descriptions = tuple{ args... }.template
			get_range_of_decayed<vk::subpass_description>();

		ci.subpass_count = (uint32) subpass_descriptions.size();
		ci.subpasses = subpass_descriptions.iterator();

		if constexpr (types<Args...>::template
			count_of_range_of_decayed<vk::subpass_dependency> > 0
		) {
			auto& subpass_dependencies = tuple{ args... }.template
				get_range_of_decayed<vk::subpass_dependency>();

			ci.dependency_count = (uint32) subpass_dependencies.size();
			ci.dependencies = subpass_dependencies.iterator();
		}

		if constexpr (types<Args...>::template
			count_of_range_of_decayed<vk::attachment_description> > 0
		) {
			auto& attachment_descriptions = tuple{ args... }.template
				get_range_of_decayed<vk::attachment_description>();

			ci.attachment_count = (uint32) attachment_descriptions.size();
			ci.attachments = attachment_descriptions.iterator();
		}

		handle<vk::instance> instance = tuple{ args... }.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = tuple{ args... }.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::render_pass> render_pass;

		vk::result result {
			vk::get_device_function<vk::create_render_pass_function>(
				instance, device
			)(
				device.underlying(),
				&ci,
				nullptr,
				&render_pass.underlying()
			)
		};

		if(result.error()) return result;

		return render_pass;

	}

	template<typename... Args>
	handle<vk::render_pass> create_render_pass(Args&&... args) {
		vk::expected<handle<vk::render_pass>> result
			= vk::try_create_render_pass(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk