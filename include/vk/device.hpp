export module vk.device;

import vk_headers;
export import <cxx_util/parameter_pack/parameter_pack.hpp>;
export import <cxx_util/parameter_pack/for_each.hpp>;
export import <cxx_util/int.hpp>;
export import <cxx_util/bitmask_from_enum.hpp>;
export import vk.physical_device;

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