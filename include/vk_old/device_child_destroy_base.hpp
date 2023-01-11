#pragma once

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/handle.hpp>

namespace vk {

	struct device;

	template<
		typename ObjectType,
		void Function(
			handle<vk::device>,
			handle<ObjectType>,
			const void*
		)
	>
	struct device_child_destroy_base {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<handle<vk::device>>,
			types::are_contain_one_decayed<handle<ObjectType>>
		>::template for_types<Args...>
		void operator() (Args&&... args) const {
			auto device = elements::decayed<handle<vk::device>>(args...);
			auto o = elements::decayed<handle<ObjectType>>(args...);

			Function(device, o, nullptr);
		}

	}; // device_child_destroy_base

} // vk