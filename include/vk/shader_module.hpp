#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/one_of.hpp>
#include <core/move.hpp>

#include "shared/result.hpp"
#include "shader/module/create_info.hpp"

namespace vk {

	class device;

	class shader_module {
		void* m_shader_module;
		const vk::device& m_device;

	public:
		shader_module(const shader_module&) = delete;

		shader_module(shader_module&& other) : m_shader_module{ other.m_shader_module }, m_device{ other.m_device } { other.m_shader_module = nullptr; };

		shader_module(VkShaderModule shader_module, const vk::device& device) : m_shader_module{ shader_module }, m_device{ device } {}

		~shader_module() {
			if(m_shader_module) {
				vkDestroyShaderModule(
					*(VkDevice*) &m_device,
					(VkShaderModule) m_shader_module,
					nullptr
				);
				m_shader_module = nullptr;
			}
		}
	};

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
		if(result.success()) return vk::shader_module{ shader_module, device };
		return result;
	}
}