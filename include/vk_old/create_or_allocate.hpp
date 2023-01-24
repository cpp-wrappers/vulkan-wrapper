#pragma once

namespace vk {


	template<typename ObjectType>
	struct create_t;

	template<typename ObjectType>
	constexpr inline vk::create_t<ObjectType> create
		= vk::create_t<ObjectType>{};


	template<typename ObjectType>
	struct allocate_t;

	template<typename ObjectType>
	constexpr inline vk::allocate_t<ObjectType> allocate
		= vk::allocate_t<ObjectType>{};

} // vk