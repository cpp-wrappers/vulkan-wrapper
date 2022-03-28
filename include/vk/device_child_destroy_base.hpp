#pragma once

#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/handle/possibly_guarded_of.hpp>

#include "handle/get_value.hpp"

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
			types::are_contain_one_possibly_guarded_handle_of<vk::device>,
			types::are_contain_one_decayed<handle<ObjectType>>
		>::template for_types<Args...>
		void operator() (Args&&... args) const {
			auto& device = elements::possibly_guarded_handle_of<vk::device>(args...);
			auto o = elements::decayed<handle<ObjectType>>(args...);

			Function(
				vk::get_handle(device),
				vk::get_handle(o),
				nullptr
			);
		}

	};

} // vk