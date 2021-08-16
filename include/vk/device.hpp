#pragma once

#include "headers.hpp"
#include <cxx_util/parameter_pack/parameter_pack.hpp>
#include <cxx_util/parameter_pack/for_each.hpp>
#include <cxx_util/int.hpp>
#include <cxx_util/bitmask_from_enum.hpp>
#include "physical_device.hpp"

namespace vk {

export struct device {
	VkDevice m_device;

	template<typename... Args>
	device(Args&&... args) {
		using PP = u::parameter_pack<Args...>;

		static_assert(PP::template count<vk::physical_device> == 1);

		u::for_each(
			args...,
			u::do_one_of {
				[&]() {
					
				}
			}
		);
	}

};

}