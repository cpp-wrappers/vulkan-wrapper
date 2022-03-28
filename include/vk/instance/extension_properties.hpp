#pragma once

#include "../extension_properties.hpp"
#include "../result.hpp"
#include "../count.hpp"
#include "../extension_name.hpp"
#include "../function.hpp"

#include <core/span.hpp>
#include <core/range/of_value_type_same_as.hpp>
#include <core/range/contains.hpp>
#include <core/range/transform.hpp>
#include <core/meta/type/disjuncted_predicates.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/elements/for_each_satisfying_type_predicate.hpp>
#include <core/meta/elements/satisfying_predicate.hpp>
#include <core/meta/elements/one_of.hpp>

extern "C" VK_ATTR int32 VK_CALL vkEnumerateInstanceExtensionProperties(
	const char* layer_name,
	uint32* property_count,
	vk::extension_properties* properties
);

namespace vk {

	template<range::of<vk::extension_properties> Range>
	vk::expected<vk::count>
	enumerate_instance_extension_properties(Range&& extension_properties) {
		uint32 count = extension_properties.size();

		vk::result result {
			vkEnumerateInstanceExtensionProperties(
				nullptr,
				&count,
				extension_properties.data()
			)
		};

		if(result.error()) return result;
		return vk::count{ count };
	}

	vk::expected<vk::count>
	inline get_instance_extension_properties_count() {
		return enumerate_instance_extension_properties(
			span<vk::extension_properties>{ nullptr, 0 }
		);
	}

	vk::expected<vk::count>
	view_instance_extension_properties(auto&& f, vk::count count) {
		vk::extension_properties extensions_props[(uint32)count];

		auto result = enumerate_instance_extension_properties(
			span{ extensions_props, (uint32)count }
		);
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

		vk::view_instance_extension_properties(
			[&](span<vk::extension_properties> props) {
				supported =
					range::contains(name)(
						range::transform(props)([](auto& extension_props) {
							return vk::extension_name{ extension_props.name };
						})
					);
			}
		);

		return supported;
	}

} // vk