#pragma once

#include <integer.hpp>

namespace vk {

	enum variant : uint32 {};
	enum major   : uint32 {};
	enum minor   : uint32 {};
	enum patch   : uint32 {};
	
	struct api_version {
		uint32 patch   : 12;
		uint32 minor   : 10;
		uint32 major   : 7;
		uint32 variant : 3;
	
		constexpr api_version(
			vk::variant variant,
			vk::major   major,
			vk::minor   minor,
			vk::patch   patch = {}
		) :
			patch{ patch }, minor{ minor }, major{ major }, variant{ variant }
		{}
	
		constexpr api_version(
			vk::major major = {},
			vk::minor minor = {},
			vk::patch patch = {}
		) :
			api_version{ vk::variant{}, major, minor, patch }
		{}

		constexpr operator uint32 () {
			return *((uint32*)this);
		}

	}; // api_version

} // vk