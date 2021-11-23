#pragma once

#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/count_of_type.hpp>
#include <core/elements/of_type.hpp>
#include <core/elements/one_of.hpp>
#include <core/move.hpp>
#include <core/exchange.hpp>

#include "../../shared/result.hpp"
#include "create_info.hpp"

namespace vk {

	class device;

	struct shader_module {
		uint64 handle;
	}; // shader_module
}