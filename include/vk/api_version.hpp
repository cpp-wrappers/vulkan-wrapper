export module vk.api_version;

export import <cinttypes>;
export import <type_traits>;
export import <cxx_util/parameter_pack/for_each.hpp>;
export import <cxx_util/int.hpp>;

export namespace vk {

struct variant : u::integral_like<uint32_t> {};
struct major : u::integral_like<uint32_t> {};
struct minor : u::integral_like<uint32_t> {};
struct patch : u::integral_like<uint32_t> {};

template<typename T>
concept version_component =
	std::is_same_v<T, variant>
	|| std::is_same_v<T, major>
	|| std::is_same_v<T, minor>
	|| std::is_same_v<T, patch>
;

struct api_version {
	uint32_t value;

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

	api_version(version_component auto... args) {
		uint32_t
			variant = 0,
			major = 0,
			minor = 0,
			patch = 0
		;

		u::for_each(
			args...,
			u::do_one_of {
				[&](vk::variant v){ variant = v; },
				[&](vk::major v){ major = v; },
				[&](vk::minor v){ minor = v; },
				[&](vk::patch v){ patch = v; }
			}
		);

		value = (variant << 29) | (major << 22) | (minor << 12) | patch;
	}
};

}