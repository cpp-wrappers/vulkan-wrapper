#pragma once

#include <core/integer.hpp>

namespace cursed {

template<typename T>
struct ptr_to_ref_like {
	T** ptr;

	ptr_to_ref_like(T** ptr) : ptr{ ptr } {}

	T& operator * () const {
		return (T&) **ptr;
	}

	auto& operator ++ () {
		++ptr;
		return *this;
	}

	auto& operator += (uint n) {
		ptr += (primitive::uint)n;
		return *this;
	}

	auto operator + (uint n) const {
		return ptr_to_ref_like{ *this } += n;
	}

	bool operator == (const ptr_to_ref_like other) const {
		return ptr == other.ptr;
	}
	//auto operator <=> (const ptr_to_ref_like&) const = default;
};

}