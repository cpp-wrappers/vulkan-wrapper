#pragma once

#include "core/primitive_integer.hpp"
#include "headers.hpp"
#include "layer_properties.hpp"
#include "result.hpp"

namespace vk {

template<typename F>
void view_layer_properties(F&& f);

class layer_properties_view {
	vk::layer_properties* m_layers_properties;
	uint32 m_count;

	layer_properties_view(
		vk::layer_properties* p_layers_properties,
		uint32 p_count
	)
		: m_layers_properties{ p_layers_properties }, m_count{ p_count }
	{}

	template<typename F>
	friend void vk::view_layer_properties(F&& f);
public:

	auto begin() const {
		return m_layers_properties;
	}

	auto end() const {
		return m_layers_properties + (primitive::uint32)m_count;
	}

	uint32 size() const {
		return m_count;
	}

	vk::layer_properties front() const {
		return *begin();
	}
}; // layers_properties_view

template<typename F>
void view_layer_properties(F&& f) {
	uint32 count;
	vk::throw_if_error(
		vkEnumerateInstanceLayerProperties(
			(primitive::uint32*)&count,
			nullptr
		)
	);

	vk::layer_properties props[(primitive::uint32)count];

	vk::throw_if_error(
		vkEnumerateInstanceLayerProperties(
			(primitive::uint32*)&count,
			(VkLayerProperties*)props
		)
	);

	layer_properties_view v{props, count};
	f(v);
}

void for_each_layer_properties(auto&& f) {
	view_layer_properties([&](auto& view) {
		for(auto& props : view) f(props);
	});
}

} // vk