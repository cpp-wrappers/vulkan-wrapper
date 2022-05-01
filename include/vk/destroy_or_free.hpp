#pragma once

namespace vk {

	template<typename ObjectType>
	struct destroy_t;

	template<typename ObjectType>
	constexpr inline vk::destroy_t<ObjectType> destroy{};

	template<typename ObjectType>
	struct free_t;

	template<typename ObjectType>
	constexpr inline vk::free_t<ObjectType> free{};

} // vk