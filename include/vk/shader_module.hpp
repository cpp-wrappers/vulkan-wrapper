#pragma once

#include "headers.hpp"
#include "device.hpp"
#include "shader_module_create_info.hpp"
#include <cxx_util/params.hpp>
#include <functional>
#include <cxx_util/named.hpp>
#include <vulkan/vulkan_core.h>
#include "result.hpp"

namespace vk {

struct code_size : u::named<uint32_t>{};
struct code : u::named<uint32_t*>{};

struct shader_module {
	VkShaderModule m_shader_module;

	template<typename...Ps>
	shader_module(Ps&&... params) noexcept(false) {
		VkDevice device;
		vk::shader_module_create_info smci{};

		u::params<Ps&...>{ params... }
			.template handle<u::required>([&](vk::device& d){ device = d.m_device; })
			.template handle<u::required>([&](code_size cs){ smci.m_code_size = cs.value; })
			.template handle<u::required>([&](code c){ smci.m_code = c.value; })
			.check_for_emptiness();
		
		vk::throw_if_error(
			vkCreateShaderModule(
				device,
				(VkShaderModuleCreateInfo*)&smci,
				nullptr,
				&m_shader_module
			)
		);
	}



};

} // vk