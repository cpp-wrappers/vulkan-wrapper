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

#include "../../shared/extension_properties.hpp"
#include "../../shared/result.hpp"
#include "../../shared/count.hpp"
#include "../../shared/extension_name.hpp"
#include "../../shared/required_or_desired.hpp"

namespace vk {

	vk::expected<vk::count>
	enumerate_instance_extension_properties(range::of_value_type<vk::extension_properties> auto&& extension_properties) {
		uint32 count = extension_properties.size();

		vk::result result {
			(int32) vkEnumerateInstanceExtensionProperties(
				nullptr,
				&count,
				(VkExtensionProperties*) extension_properties.data()
			)
		};

		if(result.error()) return result;
		return vk::count{ count };
	}

	vk::expected<vk::count>
	inline get_instance_extension_properties_count() {
		return enumerate_instance_extension_properties(span<vk::extension_properties>{ nullptr, 0 });
	}

	vk::expected<vk::count>
	view_instance_extension_properties(auto&& f, vk::count count) {
		vk::extension_properties extensions_props[(uint32)count];

		auto result = enumerate_instance_extension_properties(span{ extensions_props, (uint32)count });
		if(result.is_unexpected()) return result;

		count = result.get_expected();
		f(span{extensions_props, (uint32)count});
		return count;
	}

	template<typename F>
	vk::expected<vk::count>
	view_instance_extension_properties(F&& f) {
		auto result = get_instance_extension_properties_count();
		if(result.is_unexpected()) return result;
		return view_instance_extension_properties(
			forward<F>(f),
			result.get_expected()
		);
	}

	elements::one_of<vk::result, vk::count>
	for_each_instance_extension_properties(auto&& f, vk::count count) {
		return view_instance_extension_properties(
			[&](span<vk::extension_properties> view) {
				for(vk::extension_properties props : view)
					f(props);
			},
			count
		);
	}

	template<typename F>
	elements::one_of<vk::result, vk::count>
	for_each_instance_extension_properties(F&& f) {
		auto result = get_instance_extension_properties_count();
		if(result.is_unexpected()) return result;
		return for_each_instance_extension_properties(
			forward<F>(f),
			result.get_expected()
		);
	}

	inline bool is_instance_extension_supported(vk::extension_name name) {
		bool supported = false;

		vk::view_instance_extension_properties([&](span<vk::extension_properties> props) {
			supported =
				range::contains(name)(
					range::transform(props)([](vk::extension_properties& extension_props) {
						return vk::extension_name{ extension_props.name };
					})
				);
		});

		return supported;
	}

	template<typename... Args>
	auto view_instance_extensions(Args&&... args) {
		uint32 required_count = types::count_of_satisfying_predicate<type::vk::is_required>::for_types_of<decay<Args>...>;
		vk::extension_name required_extensions[required_count];
		uint32 required_extension = 0;

		elements::for_each_satisfying_type_predicate<type::vk::is_required>::function{[&](auto req){
			required_extensions[required_extension++] = req.value;
		}}.for_elements_of(args...);

		uint32 desired_count = types::count_of_satisfying_predicate<type::vk::is_desired>::for_types_of<decay<Args>...>;
		vk::extension_name desired_extensions[desired_count];
		uint32 desired_extension = 0;

		elements::for_each_satisfying_type_predicate<type::vk::is_desired>::function{[&](auto req){
			desired_extensions[desired_extension++] = req.value;
		}}.for_elements_of(args...);

		vk::extension_name storage[required_count + desired_count];
		uint32 index = 0;

		for(auto req : required_extensions) {
			if(!vk::is_instance_extension_supported(req)) default_unexpected_handler();
			storage[index++] = req;
		}

		for(auto des : desired_extensions) {
			if(vk::is_instance_extension_supported(des)) {
				storage[index++] = des;
			}
		}

		elements::satisfying_predicate<type::negated_predicate<
			type::disjuncted_predicates<type::vk::is_desired, type::vk::is_required>
		>>(args...)(span{ storage, index });
	};

} // vk