#pragma once

#include "../layer_properties.hpp"
#include "../result.hpp"
#include "../count.hpp"
#include "../layer_name.hpp"
#include "../headers.hpp"

#include <core/span.hpp>
#include <core/array.hpp>
#include <core/range/of_value_type_same_as.hpp>
#include <core/range/contains.hpp>
#include <core/range/transform.hpp>
#include <core/meta/type/disjuncted_predicates.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/elements/for_each_satisfying_type_predicate.hpp>
#include <core/meta/elements/satisfying_predicate.hpp>
#include <core/meta/elements/one_of.hpp>
#include <core/meta/elements/pass_satisfying_type_predicate.hpp>

extern "C" VkResult vkEnumerateInstanceLayerProperties(
	uint32_t* property_count,
	VkLayerProperties* properties
);

namespace vk {

	template<range::of<vk::layer_properties> Range>
	vk::expected<vk::count>
	enumerate_instance_layer_properties(Range&& layer_properties) {
		uint32 count = layer_properties.size();

		vk::result result {
			(int32) vkEnumerateInstanceLayerProperties(
				&count,
				(VkLayerProperties*) layer_properties.data()
			)
		};

		if(result.error()) return result;
		return vk::count{ count };
	}

	vk::expected<vk::count>
	inline get_instance_layer_properties_count() {
		return enumerate_instance_layer_properties(
			span<vk::layer_properties>{ nullptr, 0 }
		);
	}

	vk::expected<vk::count>
	view_instance_layer_properties(auto&& f, vk::count count) {
		vk::layer_properties layers_props[(uint32)count];

		auto result = enumerate_instance_layer_properties(
			span{ layers_props, (uint32)count }
		);
		if(result.is_unexpected()) return result;

		count = result.get_expected();
		f(span{layers_props, (uint32)count});
		return count;
	}

	template<typename F>
	vk::expected<vk::count>
	view_instance_layer_properties(F&& f) {
		auto result = get_instance_layer_properties_count();
		if(result.is_unexpected()) return result;
		return view_instance_layer_properties(
			forward<F>(f),
			result.get_expected()
		);
	}

	elements::one_of<vk::result, vk::count>
	for_each_instance_layer_properties(auto&& f, vk::count count) {
		return view_instance_layer_properties(
			[&](span<vk::layer_properties> view) {
				for(vk::layer_properties props : view)
					f(props);
			},
			count
		);
	}

	template<typename F>
	elements::one_of<vk::result, vk::count>
	for_each_instance_layer_properties(F&& f) {
		auto result = get_instance_layer_properties_count();
		if(result.is_unexpected()) return result;
		return for_each_instance_layer_properties(
			forward<F>(f),
			result.get_expected()
		);
	}

	inline bool is_instance_layer_supported(vk::layer_name name) {
		bool supported = false;

		vk::view_instance_layer_properties(
			[&](span<vk::layer_properties> props) {
				supported =
					range::contains(name)(
						range::transform(props)([](auto& layer_props) {
							return vk::layer_name{ layer_props.name };
						})
					);
			}
		);

		return supported;
	}

} // vk