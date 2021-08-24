#pragma once

#include "headers.hpp"
#include "layer_properties.hpp"
#include "result.hpp"

namespace vk {

template<typename F>
void view_layers_properties(F&& f);

class layers_properties_view {
	vk::layer_properties* m_layers_properties;
	uint32_t m_count;

	layers_properties_view(
		vk::layer_properties* p_layers_properties,
		uint32_t p_count
	)
		: m_layers_properties{ p_layers_properties }, m_count{ p_count }
	{}

	template<typename F>
	friend void vk::view_layers_properties(F&& f);
public:

	auto begin() const {
		return m_layers_properties;
	}

	auto end() const {
		return m_layers_properties + m_count;
	}

	uint32_t size() const {
		return m_count;
	}

	vk::layer_properties front() const {
		return *begin();
	}
}; // layers_properties_view

template<typename F>
void view_layers_properties(F&& f) {
	uint32_t count;
	vk::throw_if_error(
		vkEnumerateInstanceLayerProperties(
			&count,
			nullptr
		)
	);

	vk::layer_properties props[count];

	vk::throw_if_error(
		vkEnumerateInstanceLayerProperties(
			&count,
			(VkLayerProperties*)props
		)
	);

	layers_properties_view v{props, count};
	f(v);
}

} // vk