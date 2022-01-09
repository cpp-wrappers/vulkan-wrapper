#pragma once

#include "../../shared/create_or_allocate.hpp"
#include "../../device/handle.hpp"
#include "handle.hpp"
#include "create_info.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::shader_module> {

		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::count_of_type<vk::handle<vk::device>>::equals<1>,
				types::count_of_type<vk::code_size>::equals<1>,
				types::count_of_type<vk::code>::equals<1>
			>::for_types_of<Args...>
		)
		vk::expected<vk::handle<vk::shader_module>>
		operator () (const Args&... args) const {
			vk::shader_module_create_info ci {
				.code_size = elements::of_type<const vk::code_size&>::for_elements_of(args...),
				.code = elements::of_type<const vk::code&>::for_elements_of(args...)
			};

			const vk::handle<vk::device>& device = elements::of_type<const vk::handle<vk::device>&>::for_elements_of(args...);

			VkShaderModule shader_module;

			vk::result result {
				(int32) vkCreateShaderModule(
					(VkDevice) device.value,
					(VkShaderModuleCreateInfo*) &ci,
					nullptr,
					(VkShaderModule*) &shader_module
				)
			};

			if(result.success()) return vk::handle<vk::shader_module>{ shader_module };

			return result;
		}

	};
}