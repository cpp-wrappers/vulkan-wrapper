#pragma once

#include <core/elements/one_of.hpp>
#include <core/range/of_value_type.hpp>
#include <core/span.hpp>
#include <core/range/contains.hpp>
#include <core/range/transform.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/elements/for_each_satisfying_type_predicate.hpp>
#include <core/elements/satisfying_predicate.hpp>
#include <core/type/disjuncted_predicates.hpp>

#include "../../shared/layer_properties.hpp"
#include "../../shared/result.hpp"
#include "../../shared/count.hpp"
#include "../../shared/layer_name.hpp"
#include "../../shared/required_or_desired.hpp"

namespace vk {

	vk::expected<vk::count>
	enumerate_instance_layer_properties(range::of_value_type<vk::layer_properties> auto&& layer_properties) {
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
		return enumerate_instance_layer_properties(span<vk::layer_properties>{ nullptr, 0 });
	}

	vk::expected<vk::count>
	view_instance_layer_properties(auto&& f, vk::count count) {
		vk::layer_properties layers_props[(uint32)count];

		auto result = enumerate_instance_layer_properties(span{ layers_props, (uint32)count });
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

		vk::view_instance_layer_properties([&](span<vk::layer_properties> props) {
			supported =
				range::contains(name)(
					range::transform(props)([](vk::layer_properties& layer_props) {
						return vk::layer_name{ layer_props.name };
					})
				);
		});

		return supported;
	}

	template<typename... Args>
	auto view_instance_layers(Args&&... args) {
		uint32 required_count = types::count_of_satisfying_predicate<type::vk::is_required>::for_types_of<decay<Args>...>;
		vk::layer_name required_layers[required_count];
		uint32 required_layer = 0;

		elements::for_each_satisfying_type_predicate<type::modified_predicate<type::vk::is_required, type::decay>>::function{[&](auto req){
			required_layers[required_layer++] = req.value;
		}}.for_elements_of(args...);

		uint32 desired_count = types::count_of_satisfying_predicate<type::vk::is_desired>::for_types_of<decay<Args>...>;
		vk::layer_name desired_layers[desired_count];
		uint32 desired_layer = 0;

		elements::for_each_satisfying_type_predicate<type::modified_predicate<type::vk::is_desired, type::decay>>::function{[&](auto des){
			desired_layers[desired_layer++] = des.value;
		}}(args...);

		vk::layer_name storage[required_count + desired_count];
		uint32 index = 0;

		for(auto req : required_layers) {
			if(!vk::is_instance_layer_supported(req)) default_unexpected_handler();
			storage[index++] = req;
		}

		for(auto des : desired_layers) {
			if(vk::is_instance_layer_supported(des)) {
				storage[index++] = des;
			}
		}

		elements::satisfying_predicate<type::negated_predicate<
			type::disjuncted_predicates<type::vk::is_desired, type::vk::is_required>
		>>(args...)(span{ storage, index });
	};

} // vk