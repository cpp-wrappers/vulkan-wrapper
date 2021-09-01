#pragma once

#include <compare>

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

	auto& operator += (std::size_t n) {
		ptr += n;
		return *this;
	}

	auto operator + (std::size_t n) const {
		return ptr_to_ref_like{ *this } += n;
	}

	auto operator <=> (const ptr_to_ref_like&) const = default;
};

}