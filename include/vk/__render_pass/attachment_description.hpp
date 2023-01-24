#pragma once 

#include "attachment_load_op.hpp"
#include "attachment_store_op.hpp"

#include "../__image/layout.hpp"
#include "../__internal/sample_count.hpp"
#include "../__internal/format.hpp"

#include <enum_flags.hpp>
#include <types.hpp>
#include <tuple.hpp>

namespace vk {

	enum class attachment_description_flag {
		may_alias = 0x00000001
	};
	using attachment_description_flags = enum_flags<
		vk::attachment_description_flag
	>;
	
	struct load_op  { vk::attachment_load_op _; };
	struct store_op { vk::attachment_store_op _; };
	
	struct stencil_load_op  { vk::attachment_load_op _; };
	struct stencil_store_op { vk::attachment_store_op _; };
	
	struct attachment_description {
		vk::attachment_description_flags flags {};
		vk::format                       format;
		vk::sample_count                 samples { 1 };
		vk::load_op                      load_op {
			vk::attachment_load_op::dont_care
		};
		vk::store_op                     store_op {
			vk::attachment_store_op::dont_care
		};
		vk::stencil_load_op              stencil_load_op {
			vk::attachment_load_op::dont_care
		};
		vk::stencil_store_op             stencil_store_op {
			vk::attachment_store_op::dont_care
		};
		vk::initial_layout               initial_layout {
			vk::image_layout::undefined
		};
		vk::final_layout                 final_layout {
			vk::image_layout::undefined
		};
	
		template<typename... Args>
		requires types<Args...>::template exclusively_satisfy_predicates<
			count_of_decayed_same_as<vk::format> == 1,
			count_of_decayed_same_as<vk::sample_count> <= 1,
			count_of_decayed_same_as<vk::load_op> <= 1,
			count_of_decayed_same_as<vk::store_op> <= 1,
			count_of_decayed_same_as<vk::stencil_load_op> <= 1,
			count_of_decayed_same_as<vk::stencil_store_op> <= 1,
			count_of_decayed_same_as<vk::initial_layout> <= 1,
			count_of_decayed_same_as<vk::final_layout> <= 1
		>
		attachment_description(Args&&... args) {
			tuple a{ args... };
			format = a.template get_decayed_same_as<vk::format>();
	
			if constexpr(types<Args...>::template
				count_of_decayed_same_as<vk::sample_count> > 0
			) { samples = a.template get_decayed_same_as<vk::sample_count>(); }
	
			if constexpr(types<Args...>::template
				count_of_decayed_same_as<vk::load_op> > 0
			) { load_op = a.template get_decayed_same_as<vk::load_op>(); }
	
			if constexpr(types<Args...>::template
				count_of_decayed_same_as<vk::store_op> > 0
			) { store_op = a.template get_decayed_same_as<vk::store_op>(); }
	
			if constexpr(types<Args...>::template
				count_of_decayed_same_as<vk::stencil_load_op> > 0
			) {
				stencil_load_op = a.template
					get_decayed_same_as<vk::stencil_load_op>();
			}
	
			if constexpr(types<Args...>::template
				count_of_decayed_same_as<vk::stencil_store_op> > 0
			) {
				stencil_store_op = a.template
					get_decayed_same_as<vk::stencil_store_op>(); }
	
			if constexpr(types<Args...>::template
				count_of_decayed_same_as<vk::initial_layout> > 0
			) {
				initial_layout = a.template
					get_decayed_same_as<vk::initial_layout>(); }
	
			if constexpr(types<Args...>::template
				count_of_decayed_same_as<vk::final_layout> > 0
			) {
				final_layout = a.template
					get_decayed_same_as<vk::final_layout>();
			}

		} // constructor

	}; // attachment_description

} // vk