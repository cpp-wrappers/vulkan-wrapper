#pragma once

namespace vk {

	template<typename ObjectType>
	struct destroy_t;

	template<typename ObjectType>
	constexpr inline vk::destroy_t<ObjectType> destroy = vk::destroy_t<ObjectType>{};

	template<typename ObjectType>
	struct free_t;

	template<typename ObjectType>
	constexpr inline vk::free_t<ObjectType> free = vk::free_t<ObjectType>{};

} // vk