#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>

#include "../../result.hpp"
#include "create_info.hpp"

namespace vk {

	struct device;
	struct shader_module;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::device&>::equals<1u>,
			types::count_of_type<vk::code_size>::equals<1u>,
			types::count_of_type<vk::code>::equals<1u>
		>::for_types_of<Args...>
	)
	vk::shader_module& create_shader_module(Args&&... args) {
		vk::shader_module_create_info ci {
			.code_size = elements::of_type<vk::code_size&>::for_elements_of(args...),
			.code = elements::of_type<vk::code&>::for_elements_of(args...)
		};
		
		vk::shader_module* shader_module;

		vk::throw_if_error(
			vkCreateShaderModule(
				(VkDevice) & elements::of_type<vk::device&>::for_elements_of(args...),
				(VkShaderModuleCreateInfo*) &ci,
				nullptr,
				(VkShaderModule*) &shader_module
			)
		);

		return *shader_module;
	}
}