#pragma once

#include <core/wrapper/of_integer.hpp>
#include <core/expected.hpp>

namespace vk {

	struct result : wrapper::of_integer<int32, struct vk_result> {

		template<typename Type>
		requires types_are_same<int32, remove_reference<Type>>
		result(Type code) :
			wrapper::of_integer<int32, struct vk_result>{ code }
		{}

		bool  suboptimal() const { return (int32) *this == 1000001003; }
		bool  incomplete() const { return (int32) *this == 5; }
		bool     success() const { return (int32) *this == 0; }

		//errors
		bool       error() const { return (int32) *this < 0;}
		bool out_of_date() const { return (int32) *this == -1000001004; }
	};

	template<typename Type>
	struct expected : ::expected<Type, vk::result> {
		using base_type = ::expected<Type, vk::result>;

		using base_type::base_type;
	};

} // vk