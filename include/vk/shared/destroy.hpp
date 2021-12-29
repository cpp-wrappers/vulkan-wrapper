#pragma once

#include "headers.hpp"
#include "handle.hpp"

namespace vk {

	template<typename ObjectType>
	struct destroy_t;

	template<typename ObjectType>
	constexpr inline vk::destroy_t<ObjectType> destroy = vk::destroy_t<ObjectType>{};
}