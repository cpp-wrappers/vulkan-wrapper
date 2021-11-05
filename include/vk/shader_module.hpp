#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/one_of.hpp>
#include <core/move.hpp>

#include "shared/result.hpp"
#include "shader/module/create_info.hpp"

namespace vk {

	class shader_module {
		void* m_shader_module;

		shader_module(void* sm) : m_shader_module{ sm } {}

	public:
		shader_module(const shader_module&) = delete;
		shader_module(shader_module&&) = default;
	};

	class device;
	class shader_module;

	template<typename... Args>
	requires(
		types::are_exclusively_satsify_predicates<
			types::count_of_type<vk::device>::equals<1u>,
			types::count_of_type<vk::code_size>::equals<1u>,
			types::count_of_type<vk::code>::equals<1u>
		>::for_types_of<Args...>
	)
	elements::one_of<vk::result, vk::shader_module>
	try_create_shader_module(const Args&... args) {
		vk::shader_module_create_info ci {
			.code_size = elements::of_type<const vk::code_size&>::for_elements_of(args...),
			.code = elements::of_type<const vk::code&>::for_elements_of(args...)
		};
		
		const vk::device& device = elements::of_type<const vk::device&>::for_elements_of(args...);
		VkShaderModule shader_module;

		vk::result result {
			(uint32) vkCreateShaderModule(
				(VkDevice) * ((void**)&device),
				(VkShaderModuleCreateInfo*) &ci,
				nullptr,
				(VkShaderModule*) & shader_module
			)
		};
		if(result.success()) {
			return move(*((vk::shader_module*) & shader_module));
		}

		return result;
	}
}