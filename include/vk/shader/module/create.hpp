#pragma once

#include "handle.hpp"
#include "create_info.hpp"

#include "../../function.hpp"
#include "../../device/handle.hpp"
#include "../../create_or_allocate.hpp"

extern "C" VK_ATTR int32 VK_CALL vkCreateShaderModule(
	handle<vk::device> device,
	const vk::shader_module_create_info* create_info,
	const void* allocator,
	handle<vk::shader_module>* shader_module
);

namespace vk {

	template<>
	struct vk::create_t<vk::shader_module> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<handle<vk::device>>,
			types::are_contain_one_decayed<vk::code_size>,
			types::are_contain_one_decayed<vk::code>
		>::for_types<Args...>
		vk::expected<handle<vk::shader_module>>
		operator () (Args&&... args) const {
			vk::shader_module_create_info ci{};

			ci.code_size = elements::decayed<vk::code_size>(args...);
			ci.code = elements::decayed<vk::code>(args...);

			auto device = elements::decayed<handle<vk::device>>(args...);

			handle<vk::shader_module> shader_module;

			vk::result result {
				vkCreateShaderModule(
					device,
					&ci,
					nullptr,
					&shader_module
				)
			};

			if(result.error()) return result;

			return shader_module;
		}

	};

} // vk