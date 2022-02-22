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
	
		constexpr api_version(vk::variant variant, vk::major major, vk::minor minor, vk::patch patch = {})
			: patch{ patch }, minor{ minor }, major{ major }, variant{ variant }
		{}
	
		constexpr api_version(vk::major major = {}, vk::minor minor = {}, vk::patch patch = {})
			: api_version{ vk::variant{}, major, minor, patch }
		{}

		constexpr operator uint32 () {
			return *((uint32*)this);
		}
	};

} // vk

static_assert(sizeof(vk::api_version) == sizeof(uint32));