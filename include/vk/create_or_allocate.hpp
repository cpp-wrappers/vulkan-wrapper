#pragma once

namespace vk {
	
	template<typename ObjectType>
	inline constexpr bool is_allocatable = false;

	template<typename ObjectType>
	inline constexpr bool is_creatable = !is_allocatable<ObjectType>;

	template<typename ObjectType>
	requires(vk::is_creatable<ObjectType>)
	struct create_t;

	template<typename ObjectType>
	constexpr inline vk::create_t<ObjectType> create = vk::create_t<ObjectType>{};

	template<typename ObjectType>
	requires(vk::is_allocatable<ObjectType>)
	struct allocate_t;

	template<typename ObjectType>
	constexpr inline vk::allocate_t<ObjectType> allocate = vk::allocate_t<ObjectType>{};

} // vk