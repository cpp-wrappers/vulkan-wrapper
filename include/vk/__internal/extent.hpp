#pragma once

#include <array.hpp>
#include <math/vector.hpp>

namespace vk {

	template<uint32 S>
	struct extent;

	template<>
	struct extent<1> : math::vector<uint32, 1> {

		using math::vector<uint32, 1>::operator =;

		uint32& width() { return (*this)[0]; }
	};

	extent(uint32) -> extent<1>;

	template<>
	struct extent<2> : math::vector<uint32, 2> {
		extent() = default;

		using math::vector<uint32, 2>::operator =;

		extent(uint32 w, uint32 h) :
			math::vector<uint32, 2>{ w, h}
		{}

		uint32& width() { return (*this)[0]; }
		uint32& height() { return (*this)[1]; }
	};

	extent(uint32, uint32) -> extent<2>;

	template<>
	struct extent<3> : math::vector<uint32, 3> {

		using math::vector<uint32, 3>::operator =;

		extent() = default;

		extent(uint32 w, uint32 h, uint32 d) :
			math::vector<uint32, 3>{ w, h, d }
		{}

		extent(uint32 w, uint32 h) :
			math::vector<uint32, 3>{ w, h, uint32{ 1 } }
		{}

		extent(extent<2> two_d, uint32 d) :
			math::vector<uint32, 3>{ two_d[0], two_d[1], d }
		{}

		uint32& width() { return (*this)[0]; }
		uint32& height() { return (*this)[1]; }
		uint32& depth() { return (*this)[2]; }
	};

	extent(uint32, uint32, uint32) -> extent<3>;

} // vk