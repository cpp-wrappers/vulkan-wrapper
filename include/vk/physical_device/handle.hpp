#pragma once

#include "properties.hpp"
#include "memory_properties.hpp"
#include "queue_family_properties.hpp"

#include "../function.hpp"
#include "../surface/capabilities.hpp"
#include "../surface/present_mode.hpp"
#include "../surface/format.hpp"
#include "../surface/handle.hpp"
#include "../handle/base.hpp"
#include "../result.hpp"
#include "../queue_family_index.hpp"
#include "../count.hpp"
#include "../extension_name.hpp"
#include "../layer_name.hpp"
#include "../extension_properties.hpp"
#include "../memory_type_index.hpp"
#include "../unexpected_handler.hpp"

#include <core/forward.hpp>
#include <core/span.hpp>
#include <core/range/of_value_type_same_as.hpp>
#include <core/meta/elements/one_of.hpp>

namespace vk {

	struct device;
	struct surface;
	struct physical_device;

} // vk

template<>
struct handle<vk::physical_device> : vk::handle_base<vk::dispatchable> {

	template<typename... Args>
	[[ nodiscard ]]
	handle<vk::device>
	create_device(Args&&... args) const;

	template<typename... Args>
	[[ nodiscard ]]
	vk::physical_device_properties
	get_properties(Args&&... args) const;

	[[ nodiscard ]] inline
	vk::physical_device_memory_properties
	get_memory_properties() const;

	[[ nodiscard ]]
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
	}

	template<range::of<vk::queue_family_properties> Range>
	[[ nodiscard ]]
	vk::count
	get_queue_family_properties(Range&& range) const;

	[[ nodiscard ]] inline
	vk::count
	get_queue_family_properties_count() const;

	template<typename F>
	[[ nodiscard ]]
	vk::count
	view_queue_family_properties(vk::count count, F&& f) const;

	template<typename F>
	[[ nodiscard ]]
	vk::count
	view_queue_family_properties(F&& f) const;

	template<typename... Args>
	requires(types::are_same::for_types<Args..., vk::queue_flag>)
	vk::queue_family_index
	find_first_queue_family_index_with_capabilities(Args... args) const {
		uint32 count = (uint32) get_queue_family_properties_count();
		vk::queue_family_properties props[count];
		get_queue_family_properties(span{ props, count });
		uint32 index = 0;
		for(vk::queue_family_properties p : span{ props, count }) {
			if((p.flags.get(args) && ...)) return { index };
			++index;
		}
		return { vk::queue_family_ignored };
	}

	vk::count for_each_queue_family_properties(auto&& f) const {
		return view_queue_family_properties(
			[&](auto view) {
				for(auto props : view) f(props);
			}
		);
	}

	template<typename... Args>
	[[ nodiscard ]]
	vk::count enumerate_device_extension_properties(Args&&...) const;

	[[ nodiscard ]] inline
	vk::count
	get_device_extension_properties_count(vk::layer_name layer_name = {}) const;

	template<typename F>
	vk::count
	view_device_extension_properties(
		vk::count count, F&& f, vk::layer_name layer_name = {}
	) const;

	template<typename F>
	vk::count
	view_device_extension_properties(
		F&& f, vk::layer_name layer_name = {}
	) const;

	template<typename F>
	vk::count
	for_each_device_extension_properties(
		F&& f, vk::layer_name layer_name = {}
	) const;

	template<typename... Args>
	vk::surface_capabilities
	get_surface_capabilities(Args&&... args) const;

	template<typename... Args>
	[[ nodiscard ]]
	vk::count
	get_surface_formats(Args&&... args) const;

	[[ nodiscard ]] inline
	vk::surface_format
	get_first_surface_format(handle<vk::surface> surface) const;

	[[ nodiscard ]]
	vk::count inline
	get_surface_format_count(handle<vk::surface> surface) const;

	template<typename F>
	[[ nodiscard ]]
	vk::count
	view_surface_formats(
		handle<vk::surface> surface, vk::count count, F&& f
	) const;

	template<typename F>
	[[ nodiscard ]]
	vk::count
	view_surface_formats(handle<vk::surface> surface, F&& f) const;

	template<typename... Args>
	vk::count
	get_surface_present_modes(Args&&... args) const;

	vk::count
	get_surface_present_mode_count(handle<vk::surface> surface) const;

	template<typename F>
	vk::count
	view_surface_present_modes(
		handle<vk::surface> surface, vk::count count, F&& f
	) const;

	template<typename F>
	vk::count
	view_surface_present_modes(handle<vk::surface> surface, F&& f) const;

	template<typename F>
	vk::count
	for_each_surface_presesnt_mode(handle<vk::surface> surface, F&& f) const;

	template<typename... Args>
	bool
	get_surface_support(Args&&...) const;

	template<typename... Args>
	void get_features(Args&&... args) const;

}; // handle<physical_device>

#include "get_properties.hpp"
#include "get_queue_family_properties.hpp"
#include "get_queue_family_properties_count.hpp"
#include "view_queue_family_properties.hpp"
#include "get_memory_properties.hpp"
#include "get_surface_capabilities.hpp"
#include "get_surface_formats.hpp"
#include "get_surface_format_count.hpp"
#include "get_first_surface_format.hpp"
#include "view_surface_formats.hpp"
#include "get_surface_present_modes.hpp"
#include "get_features.hpp"
#include "get_surface_support.hpp"
#include "enumerate_device_extension_properties.hpp"
#include "get_device_extension_properties_count.hpp"
#include "view_device_extension_properties.hpp"
#include "for_each_device_extension_properties.hpp"

#include "../device/create.hpp"

template<typename... Args>
handle<vk::device>
handle<vk::physical_device>::create_device(Args&&... args) const {
	return vk::create<vk::device>(*this, forward<Args>(args)...);
}