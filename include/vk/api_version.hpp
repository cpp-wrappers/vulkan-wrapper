export module vk.api_version;

export import <cinttypes>;
export import <type_traits>;
export import <cxx_util/parameter_pack/for_each.hpp>;

export namespace vk {
	struct variant { uint32_t value; };
	struct major { uint32_t value; };
	struct minor { uint32_t value; };
	struct patch { uint32_t value; };
	
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

		api_version(version_component auto... args) {
			uint32_t
				variant = 0,
				major = 0,
				minor = 0,
				patch = 0
			;

			u::for_each(
				u::combined {
					[&](vk::variant v){ variant = v.value; },
					[&](vk::major v){ major = v.value; },
					[&](vk::minor v){ minor = v.value; },
					[&](vk::patch v){ patch = v.value; }
				}
			);

			value = (variant << 29) | (major << 22) | (minor << 12) | patch;
		}
	};
}