#pragma once

#include <core/wrapper/of_integer.hpp>

namespace vk {

	struct variant : wrapper::of_integer<uint32> {};
	struct major : wrapper::of_integer<uint32> {};
	struct minor : wrapper::of_integer<uint32> {};
	struct patch : wrapper::of_integer<uint32> {};
	
	struct api_version {
		uint32 patch : 12;
		uint32 minor : 10;
		uint32 major : 7;
		uint32 variant : 3;
	
		api_version(vk::variant variant, vk::major major, vk::minor minor, vk::patch patch = {})
			: variant{ variant }, major{ minor }, minor{ minor }, patch{ patch }
		{}
	
		api_version(vk::major major = {}, vk::minor minor = {}, vk::patch patch = {})
			: api_version{ vk::variant{ 0u }, major, minor, patch }
		{}
	};
}

static_assert(sizeof(vk::api_version) == sizeof(uint32));