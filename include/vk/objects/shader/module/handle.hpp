#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/one_of.hpp>
#include <core/move.hpp>
#include <core/exchange.hpp>

#include "../../../object/handle/base.hpp"
#include "create_info.hpp"

namespace vk {

	struct shader_module;

	template<>
	struct vk::handle<vk::shader_module> : vk::handle_base<vk::non_dispatchable> {
	};
} // vk