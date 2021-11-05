#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/one_of.hpp>

#include "../../shared/result.hpp"
#include "create_info.hpp"

namespace vk::internal {

	struct device;
	struct shader_module;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::internal::device*>::equals<1u>,
			types::count_of_type<vk::code_size>::equals<1u>,
			types::count_of_type<vk::code>::equals<1u>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::internal::shader_module*>
	create_shader_module(Args... args) {
		vk::shader_module_create_info ci {
			.code_size = elements::of_type<vk::code_size&>::for_elements_of(args...),
			.code = elements::of_type<vk::code&>::for_elements_of(args...)
		};
		
		vk::internal::shader_module* shader_module;

		vk::result result {
			(uint32) vkCreateShaderModule(
				(VkDevice) elements::of_type<vk::internal::device*&>::for_elements_of(args...),
				(VkShaderModuleCreateInfo*) &ci,
				nullptr,
				(VkShaderModule*) &shader_module
			)
		};
		if(result.success()) {
			return shader_module;
		}

		return result;
	}
}