#pragma once

#include "./handle.hpp"
#include "./create_info.hpp"
#include "../__internal/function.hpp"
#include "../__internal/result.hpp"
#include "../__internal/unexpected_handler.hpp"
#include "../__device/handle.hpp"

#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	struct create_shader_module_function : vk::function<int32(*)(
		handle<vk::device>::underlying_type device,
		const vk::shader_module_create_info* create_info,
		const void* allocator,
		handle<vk::shader_module>::underlying_type* shader_module
	)> {
		static constexpr auto name = "vkCreateShaderModule";
	};

	template<typename... Args>
	requires types<Args...>::template exclusively_satisfy_predicates<
		count_of_decayed_same_as<handle<vk::instance>> == 1,
		count_of_decayed_same_as<handle<vk::device>> == 1,
		count_of_decayed_same_as<vk::code_size> == 1,
		count_of_decayed_same_as<vk::code> == 1
	>
	vk::expected<handle<vk::shader_module>>
	try_create_shader_module(Args&&... args) {
		vk::shader_module_create_info ci{};

		ci.code_size = tuple{ args... }.template
			get_decayed_same_as<vk::code_size>();
		ci.code = tuple{ args... }.template
			get_decayed_same_as<vk::code>();

		handle<vk::instance> instance = tuple{ args... }.template
			get_decayed_same_as<handle<vk::instance>>();

		handle<vk::device> device = tuple{ args... }.template
			get_decayed_same_as<handle<vk::device>>();

		handle<vk::shader_module> shader_module;

		vk::result result {
			vk::get_device_function<vk::create_shader_module_function>(
				instance, device
			)(
				device.underlying(),
				&ci,
				nullptr,
				&shader_module.underlying()
			)
		};

		if(result.error()) return result;

		return shader_module;
	}

	template<typename... Args>
	handle<vk::shader_module> create_shader_module(Args&&... args) {
		vk::expected<handle<vk::shader_module>> result
			= vk::try_create_shader_module(forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	}

} // vk