#pragma once

#include "../../../object/create_or_allocate.hpp"
#include "../../device/handle.hpp"
#include "handle.hpp"
#include "create_info.hpp"

namespace vk {

	template<>
	struct vk::create_t<vk::shader_module> {

		template<typename... Args>
		requires types::are_exclusively_satsify_predicates<
			types::vk::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::count_of_type<vk::code_size>::equals<1>::ignore_const::ignore_reference,
			types::count_of_type<vk::code>::equals<1>::ignore_const::ignore_reference
		>::for_types_of<Args...>
		vk::expected<vk::handle<vk::shader_module>>
		operator () (Args&&... args) const {
			vk::shader_module_create_info ci{};

			ci.code_size = elements::of_type<vk::code_size>::ignore_const::ignore_reference::for_elements_of(args...);
			ci.code = elements::of_type<vk::code>::ignore_const::ignore_reference::for_elements_of(args...);

			auto& device = elements::vk::possibly_guarded_handle_of<vk::device>::for_elements_of(args...);

			vk::handle<vk::shader_module> shader_module;

			vk::result result {
				(int32) vkCreateShaderModule(
					(VkDevice) vk::get_handle_value(device),
					(VkShaderModuleCreateInfo*) &ci,
					(VkAllocationCallbacks*) nullptr,
					(VkShaderModule*) &shader_module
				)
			};

			if(result.error()) return result;

			return shader_module;
		}

	};

} // vk