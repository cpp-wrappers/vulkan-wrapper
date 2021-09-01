#pragma once

#include "headers.hpp"
#include "device_create_info.hpp"
#include "result.hpp"
#include "queue_family_index.hpp"
#include <core/tuple.hpp>
#include "command_pool.hpp"
#include "command_pool_create_info.hpp"
#include "shader_module.hpp"
#include "shader_module_create_info.hpp"
#include "render_pass.hpp"

namespace vk {

struct device {

	template<typename... Args>
	requires(
		types::of<Args...>::template count_of_type<vk::queue_family_index> == 1 &&
		(
			types::of<Args...>::size - 1
			-
			types::of<Args...>::template count_of_type<vk::command_pool_create_flag>
		) == 0
	)
	vk::command_pool& create_command_pool(Args&&... args) const {
		vk::command_pool_create_info ci{};

		tuple{ args... }
			.get([&](vk::queue_family_index i) {
				ci.m_queue_family_index = i;
			})
			.get([&](vk::command_pool_create_flag f) {
				ci.m_flags.set(f);
			});

		VkCommandPool command_pool;

		vk::throw_if_error(
			vkCreateCommandPool(
				(VkDevice)this,
				(VkCommandPoolCreateInfo*)&ci,
				nullptr,
				&command_pool
			)
		);

		return *((vk::command_pool*)command_pool);
	}

	template<typename... Args>
	requires(
		types::of<Args...>::template count_of_type<code_size> == 1 &&
		types::of<Args...>::template count_of_type<code> == 1 &&
		types::of<Args...>::size == 2
	)
	vk::shader_module& create_shader_module(Args&&... args) const {
		vk::shader_module_create_info ci{};

		tuple{ args... }
			.get([&](vk::code_size cs) {
				ci.m_code_size = cs.value;
			})
			.get([&](vk::code c) {
				ci.m_code = c.value;
			});
		
		VkShaderModule shader_module;

		vk::throw_if_error(
			vkCreateShaderModule(
				(VkDevice)this,
				(VkShaderModuleCreateInfo*)&ci,
				nullptr,
				&shader_module
			)
		);

		return *((vk::shader_module*)shader_module);
	}

};

}