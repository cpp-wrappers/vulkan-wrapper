#pragma once

#include "core/primitive_integer.hpp"
#include <core/integer.hpp>

namespace vk {

struct variant : uint32 {};
struct major : uint32 {};
struct minor : uint32 {};
struct patch : uint32 {};

struct api_version {
	primitive::uint32 patch : 12;
	primitive::uint32 minor : 10;
	primitive::uint32 major : 7;
	primitive::uint32 variant : 3;

	api_version(vk::variant variant, vk::major major, vk::minor minor, vk::patch patch = {})
		: variant{ variant }, major{ minor }, minor{ minor }, patch{ patch }
	{}

	api_version(vk::major major = {}, vk::minor minor = {}, vk::patch patch = {})
		: api_version{ vk::variant{ 0u }, major, minor, patch }
	{}
};

static_assert(sizeof(api_version) == sizeof(uint32));

}