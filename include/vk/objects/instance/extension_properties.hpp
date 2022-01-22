#pragma once

#include "../../shared/extension_properties.hpp"
#include "../../shared/result.hpp"
#include "../../shared/count.hpp"
#include "../../shared/extension_name.hpp"

#include <core/span.hpp>
#include <core/range/of_value_type.hpp>
#include <core/range/contains.hpp>
#include <core/range/transform.hpp>
#include <core/meta/type/disjuncted_predicates.hpp>
#include <core/meta/types/are_exclusively_satsify_predicates.hpp>
#include <core/meta/elements/for_each_satisfying_type_predicate.hpp>
#include <core/meta/elements/satisfying_predicate.hpp>
#include <core/meta/elements/one_of.hpp>

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

} // vk