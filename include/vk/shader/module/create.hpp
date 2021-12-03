#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/one_of.hpp>

#include "../../shared/result.hpp"
#include "handle.hpp"
#include "create_info.hpp"
#include "../../device/handle.hpp"

namespace vk {

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::device>::equals<1>,
			types::count_of_type<vk::code_size>::equals<1>,
			types::count_of_type<vk::code>::equals<1>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::shader_module> try_create_shader_module(const Args&... args) {
		vk::shader_module_create_info ci {
			.code_size = elements::of_type<const vk::code_size&>::for_elements_of(args...),
			.code = elements::of_type<const vk::code&>::for_elements_of(args...)
		};
		
		const vk::device& device = elements::of_type<const vk::device&>::for_elements_of(args...);

		VkShaderModule shader_module;
		
		vk::result result {
			(int32) vkCreateShaderModule(
				(VkDevice) device.handle,
				(VkShaderModuleCreateInfo*) &ci,
				nullptr,
				(VkShaderModule*) &shader_module
			)
		};

		if(result.success()) return vk::shader_module{ shader_module };

		return result;
	}
}