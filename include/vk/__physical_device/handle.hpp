#pragma once

#include <handle.hpp>

namespace vk {

	struct physical_device;

} // vk

template<>
struct handle_underlying_t<vk::physical_device> {
	using type = vk::physical_device*;
	static constexpr type invalid = nullptr;
};

template<>
struct handle_interface<vk::physical_device> :
	handle_interface_base<vk::physical_device>
{

	/* template<typename ObjectType, typename... Args>
	[[ nodiscard ]]
	auto create(Args&&... args) const {
		auto result = vk::create<ObjectType>(*this, forward<Args>(args)...);
		if(result.is_unexpected()) {
			vk::unexpected_handler(result.get_unexpected());
		}
		return result.get_expected();
	} */

	/* template<typename... Args>
	[[ nodiscard ]]
	vk::physical_device_properties
	get_properties(Args&&...) const; */

	/* [[ nodiscard ]] inline
	vk::physical_device_memory_properties
	get_memory_properties() const; */

	/* [[ nodiscard ]]
	vk::memory_type_index
	find_first_memory_type_index(
		vk::memory_properties required_properties,
		vk::memory_type_indices required_indices
	) const {
		auto physical_device_memory_properties = get_memory_properties();

		for(
			uint32 i = 0;
			i < physical_device_memory_properties.memory_type_count;
			++i
		) {
			bool required_type = required_indices.at(i);
			auto memory_type =
				physical_device_memory_properties.memory_types[i];

			bool meets_required_properties =
				(memory_type.properties.value & required_properties.value)
				== required_properties.value;

			if(required_type && meets_required_properties) {
				return (vk::memory_type_index) i;
			}
		}

		vk::unexpected_handler();
	} */

	/* template<range_of<vk::queue_family_properties> Range>
	[[ nodiscard ]]
	vk::count get_queue_family_properties(Range&&) const; */

	/* [[ nodiscard ]] inline
	vk::count get_queue_family_properties_count() const; */

	/* template<typename Handler>
	void view_queue_family_properties(vk::count, Handler&&) const; */

	/* template<typename Handler>
	void view_queue_family_properties(Handler&&) const; */

	/* template<typename... Args>
	requires types::are_same::for_types<Args..., vk::queue_flag>
	vk::queue_family_index
	find_first_queue_family_with_capabilities(Args... args) const {
		uint32 count = (uint32) get_queue_family_properties_count();
		vk::queue_family_properties props[count];
		count = get_queue_family_properties(span{ props, count });
		uint32 index = 0;
		for(vk::queue_family_properties p : span{ props, count }) {
			if((p.flags.get(args) && ...))
				return vk::queue_family_index{ index };
			++index;
		}
		return vk::queue_family_ignored;
	} */

	/* vk::queue_family_index
	find_first_graphics_queue_family() {
		return find_first_queue_family_with_capabilities(
			vk::queue_flag::graphics
		);
	} */

	/* template<typename Handler>
	void for_each_queue_family_properties(Handler&&) const; */

	/* template<typename... Args>
	[[ nodiscard ]]
	vk::count enumerate_device_extension_properties(Args&&...) const; */

	/* [[ nodiscard ]] vk::count inline
	get_device_extension_properties_count(vk::layer = {}) const; */

	/* template<typename Handler>
	void view_device_extension_properties(
		vk::count, Handler&&, vk::layer = {}
	) const; */

	/* template<typename Handler>
	void view_device_extension_properties(Handler&&, vk::layer = {}) const; */

	/* template<typename Handler>
	void for_each_device_extension_properties(Handler&&, vk::layer = {}) const; */

	/* template<typename... Args>
	vk::surface_capabilities
	get_surface_capabilities(Args&&...) const; */

	/* template<typename... Args>
	[[ nodiscard ]]
	vk::count get_surface_formats(Args&&...) const; */

	/* [[ nodiscard ]] inline
	vk::surface_format get_first_surface_format(handle<vk::surface>) const; */

	/* [[ nodiscard ]]
	vk::count inline get_surface_format_count(handle<vk::surface>) const; */

	/* template<typename Handler>
	void view_surface_formats(handle<vk::surface>, vk::count, Handler&&) const; */

	/* template<typename Handler>
	void view_surface_formats(handle<vk::surface>, Handler&&) const; */

	/* template<typename... Args>
	vk::count get_surface_present_modes(Args&&...) const; */

	/* [[ nodiscard ]] inline
	vk::count get_surface_present_mode_count(handle<vk::surface>) const; */

	/* template<typename Handler>
	void
	view_surface_present_modes(handle<vk::surface>, vk::count, Handler&&) const; */

	/* template<typename Handler>
	void view_surface_present_modes(handle<vk::surface>, Handler&&) const; */

	/* template<typename Handler>
	void for_each_surface_presesnt_mode(handle<vk::surface>, Handler&&) const; */

	/* template<typename... Args>
	[[ nodiscard ]]
	bool get_surface_support(Args&&...) const; */

	/* template<typename... Args>
	void get_features(Args&&...) const; */

}; // handle<physical_device>