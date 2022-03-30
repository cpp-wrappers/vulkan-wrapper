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
#include "../handle/get_value.hpp"
#include "../result.hpp"
#include "../queue_family_index.hpp"
#include "../count.hpp"
#include "../extension_name.hpp"
#include "../layer_name.hpp"
#include "../extension_properties.hpp"
#include "../memory_type_index.hpp"
#include "../unexpected_handler.hpp"

#include <core/handle/possibly_guarded_of.hpp>
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
	handle<vk::device>
	create_device(Args&&... args) const;

	template<typename... Args>
	guarded_handle<vk::device>
	create_guarded_device(Args&&... args) const;

	template<typename... Args>
	vk::physical_device_properties
	get_properties(Args&&... args) const;

	vk::physical_device_memory_properties inline
	get_memory_properties() const;

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
	vk::count
	get_queue_family_properties(Range&& range) const;

	vk::count inline
	queue_family_properties_count() const;

	vk::count
	view_queue_family_properties(vk::count count, auto&& f) const;

	template<typename F>
	vk::count
	view_queue_family_properties(F&& f) const;

	template<typename... Args>
	requires(types::are_same::for_types<Args..., vk::queue_flag>)
	vk::queue_family_index
	find_first_queue_family_index_with_capabilities(Args... args) const {
		uint32 count = (uint32)queue_family_properties_count();
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
	vk::count enumerate_extension_properties(Args&&...) const;

	vk::count inline
	get_extension_properties_count(vk::layer_name name = {}) const;

	vk::count
	view_extension_properties(
		vk::count count, auto&& f, vk::layer_name name = {}
	) const;

	template<typename F>
	vk::count
	view_extension_properties(F&& f, vk::layer_name name = {}) const;

	vk::count
	for_each_extension_properties(auto&& f) const;

	template<typename... Args>
	vk::surface_capabilities
	get_surface_capabilities(Args&&... args) const;

	template<typename... Args>
	vk::count
	get_surface_formats(Args&&... args) const;

	template<possibly_guarded_handle_of<vk::surface> Surface>
	vk::surface_format
	get_first_surface_format(Surface& surface) const;

	template<possibly_guarded_handle_of<vk::surface> Surface>
	vk::count
	get_surface_formats_count(Surface& surface) const;

	template<possibly_guarded_handle_of<vk::surface> Surface, typename F>
	vk::count
	view_surface_formats(Surface& surface, vk::count count, F&& f) const;

	template<possibly_guarded_handle_of<vk::surface> Surface, typename F>
	vk::count
	view_surface_formats(Surface& surface, F&& f) const;

	template<typename... Args>
	vk::count
	get_surface_present_modes(Args&&... args) const;

	template<possibly_guarded_handle_of<vk::surface> Surface>
	vk::count
	get_surface_present_mode_count(Surface& surface) const;

	template<possibly_guarded_handle_of<vk::surface> Surface, typename F>
	vk::count
	view_surface_present_modes(Surface& surface, vk::count count, F&& f) const;

	template<possibly_guarded_handle_of<vk::surface> Surface, typename F>
	vk::count
	view_surface_present_modes(Surface& surface, F&& f) const;

	template<possibly_guarded_handle_of<vk::surface> Surface, typename F>
	vk::count
	for_each_surface_presesnt_mode(Surface& surface, F&& f) const;

	template<typename... Args>
	bool
	get_surface_support(Args&&...) const;

	template<typename... Args>
	void get_features(Args&&... args) const;

}; // handle<physical_device>

#include "get_properties.hpp"
#include "get_queue_family_properties.hpp"
#include "get_memory_properties.hpp"
#include "get_surface_capabilities.hpp"
#include "get_surface_formats.hpp"
#include "get_surface_present_modes.hpp"
#include "get_features.hpp"
#include "get_surface_support.hpp"
#include "enumerate_extension_properties.hpp"

#include "../device/create.hpp"
#include "../device/guarded_handle.hpp"

template<typename... Args>
handle<vk::device>
handle<vk::physical_device>::create_device(Args&&... args) const {
	return vk::create<vk::device>(*this, forward<Args>(args)...);
}

template<typename... Args>
guarded_handle<vk::device>
handle<vk::physical_device>::create_guarded_device(Args&&... args) const {
	auto result = vk::create<vk::device>(*this, forward<Args>(args)...);
	if(result.is_unexpected()) {
		vk::unexpected_handler(result.get_unexpected());
	}
	return { result.get_expected() };
}