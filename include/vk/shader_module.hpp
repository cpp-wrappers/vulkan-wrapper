#pragma once

#include "shader/module/create.hpp"

namespace vk {

	class shader_module {
		vk::internal::shader_module* m_shader_module;

		shader_module(vk::internal::shader_module* sm) : m_shader_module{ sm } {}

	public:
	
		friend class device;
	};

	template<typename... Args>
	requires requires(vk::internal::device& d, const Args&... args) {
		vk::internal::create_shader_module(d, args...);
	}
	vk::shader_module create_shader_module(const Args&... args) const {
		return {
			vk::internal::create_shader_module(
				m_device,
				args...
			).template get<vk::internal::shader_module*>()
		};
	}
}