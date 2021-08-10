export module vk.api_version;

export import <cinttypes>;
export import <type_traits>;
export import <cxx_util/parameter_pack/for_each.hpp>;

export namespace vk {

struct variant { uint32_t value; operator uint32_t() const { return value; }};
struct major { uint32_t value; operator uint32_t() const { return value; }};
struct minor { uint32_t value; operator uint32_t() const { return value; }};
struct patch { uint32_t value; operator uint32_t() const { return value; }};

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
			u::combined {
				[&](vk::variant v){ variant = v; },
				[&](vk::major v){ major = v; },
				[&](vk::minor v){ minor = v; },
				[&](vk::patch v){ patch = v; }
			},
			args...
		);

		value = (variant << 29) | (major << 22) | (minor << 12) | patch;
	}
};

}