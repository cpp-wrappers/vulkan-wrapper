#pragma once

#include <expected.hpp>

namespace vk {

	struct result {
		int32 code;

		template<same_as<int32> Type>
		result(Type code) : code{ code } {}

		bool  suboptimal() const { return code == 1000001003; }
		bool  incomplete() const { return code == 5; }
		bool     success() const { return code == 0; }

		//errors
		bool       error() const { return code < 0;}
		bool out_of_date() const { return code == -1000001004; }
	};

	template<typename Type>
	struct expected : ::expected<Type, vk::result> {
		using base_type = ::expected<Type, vk::result>;
		using base_type::base_type;
	};

} // vk