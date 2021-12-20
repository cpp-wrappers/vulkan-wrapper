#pragma once

#include <core/elements/one_of.hpp>
#include <core/range/of_value_type.hpp>
#include <core/span.hpp>
#include <core/range/is_contains.hpp>
#include <core/range/transform.hpp>

#include "../shared/layer_properties.hpp"
#include "../shared/result.hpp"
#include "../shared/count.hpp"
#include "../shared/layer_name.hpp"

namespace vk {

	elements::one_of<vk::result, vk::count>
	try_enumerate_instance_layer_properties(
		range::of_value_type<vk::layer_properties> auto&& layer_properties
	) {
		uint32 count = layer_properties.size();

		vk::result result {
			(int32) vkEnumerateInstanceLayerProperties(
				&count,
				(VkLayerProperties*) layer_properties.data()
			)
		};

		if(result.success()) return vk::count{ count };
		return result;
	}

	elements::one_of<vk::result, vk::count>
	inline try_get_instance_layer_properties_count() {
		return try_enumerate_instance_layer_properties(span<vk::layer_properties>{ nullptr, 0 });
	}

	elements::one_of<vk::result, vk::count>
	try_view_instance_layer_properties(auto&& f, vk::count count) {
		vk::layer_properties layers_props[(uint32)count];

		auto result = try_enumerate_instance_layer_properties(span{ layers_props, (uint32)count });
		if(result.is_current<vk::result>()) return result.get<vk::result>();

		count = result.get<vk::count>();
		f(span{layers_props, (uint32)count});
		return count;
	}

	template<typename F>
	elements::one_of<vk::result, vk::count>
	try_view_instance_layer_properties(F&& f) {
		auto result = try_get_instance_layer_properties_count();
		if(result.is_current<vk::result>()) return result;
		return try_view_instance_layer_properties(forward<F>(f), result.get<vk::count>());
	}

	template<typename F>
	vk::count view_instance_layer_properties(F&& f) {
		auto result = try_view_instance_layer_properties(forward<F>(f));
		if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
		return result.template get<vk::count>();
	}

	elements::one_of<vk::result, vk::count>
	try_for_each_instance_layer_properties(auto&& f, vk::count count) {
		return try_view_instance_layer_properties([&](span<vk::layer_properties> view) {
			for(vk::layer_properties props : view)
				f(props);
		}, count);
	}

	template<typename F>
	elements::one_of<vk::result, vk::count>
	try_for_each_instance_layer_properties(F&& f) {
		auto result = try_get_instance_layer_properties_count();
		if(result.is_current<vk::result>()) return result;
		return try_for_each_instance_layer_properties(forward<F>(f), result.get<vk::count>());
	}

	template<typename F>
	vk::count for_each_instance_layer_properties(F&& f) {
		auto result = try_for_each_instance_layer_properties(forward<F>(f));
		if(result.template is_current<vk::result>()) throw result.template get<vk::result>();
		return result.template get<vk::count>();
	}

	inline bool is_instance_layer_supported(vk::layer_name name) {
		bool supported = false;

		vk::view_instance_layer_properties([&](span<vk::layer_properties> props) {
			supported =
				range::is_contains(name).for_range(
					range::transform(props).elements([](vk::layer_properties& a) {
						return vk::layer_name{ a.name };
					})
				);
		});

		return supported;
	}

}