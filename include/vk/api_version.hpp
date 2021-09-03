#pragma once

#include <type_traits>

#include <core/named.hpp>
#include <core/is.hpp>
#include <core/tuple.hpp>

namespace vk {

struct variant : named<uint32_t> {};
struct major : named<uint32_t> {};
struct minor : named<uint32_t> {};
struct patch : named<uint32_t> {};

template<typename T>
concept version_component =
	   is::type<T>::template same_as<variant>
	|| is::type<T>::template same_as<major>
	|| is::type<T>::template same_as<minor>
	|| is::type<T>::template same_as<patch>
;

class api_version {
	uint32_t value{ 0 };
public:

	operator uint32_t() const {
		return value;
	}

	vk::variant variant() {
		return { value >> 29 };
	}

	vk::major major() {
		return { (value >> 22) & 0b1111111 };
	}

	vk::minor minor() {
		return { (value >> 12) & 0b1111111111 };
	}

	vk::patch patch() {
		return { value & 0b111111111111 };
	}

	template<typename... Args>
	requires(
		types::of<Args...>::template count_of_same_as_type<vk::variant> <= 1 &&
		types::of<Args...>::template count_of_same_as_type<vk::major> <= 1 && 
		types::of<Args...>::template count_of_same_as_type<vk::minor> <= 1 &&
		types::of<Args...>::template count_of_same_as_type<vk::patch> <= 1 &&
		types::of<Args...>::template erase_same_as_one_of_types<
			vk::variant,
			vk::major,
			vk::minor,
			vk::patch
		>::empty
	)
	api_version(Args... args) {
		uint32_t
			variant = 0,
			major = 0,
			minor = 0,
			patch = 0
		;

		tuple{ std::forward<Args>(args)... }
			.get([&](vk::variant v) {
				variant = v.value;
			})
			.get([&](vk::major v) {
				major = v.value;
			})
			.get([&](vk::minor v) {
				minor = v.value;
			})
			.get([&](vk::patch v) {
				patch = v.value;
			})
		;

		value = (variant << 29) | (major << 22) | (minor << 12) | patch;
	}
};

}