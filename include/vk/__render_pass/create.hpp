#pragma once

#include <numbers.hpp>

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
		is_same_as<handle<vk::instance>>.decayed == 1,
		is_same_as<handle<vk::device>>.decayed == 1,
		is_range_of<vk::is_subpass_description.decayed> <= 1,
		is_range_of<is_same_as<vk::subpass_dependency>.decayed> <= 1,
		is_range_of<is_same_as<vk::attachment_description>.decayed> <= 1
	>
	vk::expected<handle<vk::render_pass>>
	try_create_render_pass(Args&&... args) {
		tuple a{args...};

		vk::render_pass_create_info ci{};

		basic_range auto& subpasses = a.template
			get<is_range_of<is_subpass_description.decayed>>();

		ci.subpass_count = (uint32) subpasses.size();

		vk::_subpass_description subpasses_raw[
			numbers{ci.subpass_count, (uint32) 1}.max()
		];
		for (auto [index, subpass] : subpasses.indexed_view()) {
			subpasses_raw[index] = (vk::_subpass_description) subpass;
		}

		ci.subpasses = subpasses_raw;

		if constexpr (types<Args...>::template
			count_of<is_range_of<
				is_same_as<vk::subpass_dependency>.decayed
			>> > 0
		) {
			auto& subpass_dependencies = a.template
				get<is_range_of<is_same_as<vk::subpass_dependency>.decayed>>();

			ci.dependency_count = (uint32) subpass_dependencies.size();
			ci.dependencies = subpass_dependencies.iterator();
		}

		if constexpr (types<Args...>::template
			count_of<is_range_of<
				is_same_as<vk::attachment_description>.decayed
			>> > 0
		) {
			auto& attachment_descriptions = a.template
				get<is_range_of<is_same_as<vk::attachment_description>.decayed>>();

			ci.attachment_count = (uint32) attachment_descriptions.size();
			ci.attachments = attachment_descriptions.iterator();
		}

		handle<vk::instance> instance = a.template
			get<is_same_as<handle<vk::instance>>.decayed>();

		handle<vk::device> device = a.template
			get<is_same_as<handle<vk::device>>.decayed>();

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

		if (result.error()) return result;

		return render_pass;

	}

	template<typename... Args>
	handle<vk::render_pass> create_render_pass(Args&&... args) {
		vk::expected<handle<vk::render_pass>> result
			= vk::try_create_render_pass(forward<Args>(args)...);
		if (result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk