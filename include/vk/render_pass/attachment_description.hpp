#pragma once 

#include "attachment_load_op.hpp"
#include "attachment_store_op.hpp"

#include "../image/layout.hpp"
#include "../sample_count.hpp"
#include "../format.hpp"

#include <core/flag_enum.hpp>
#include <core/wrapper/of.hpp>
#include <core/meta/decayed_same_as.hpp>
#include <core/meta/types/are_exclusively_satisfying_predicates.hpp>

namespace vk {

	enum class attachment_description_flag {
		may_alias = 0x00000001
	};
	
	struct load_op : wrapper::of<vk::attachment_load_op> {};
	struct store_op : wrapper::of<vk::attachment_store_op> {};
	
	struct stencil_load_op : wrapper::of<vk::attachment_load_op> {};
	struct stencil_store_op : wrapper::of<vk::attachment_store_op> {};
	
	struct attachment_description {
		flag_enum<attachment_description_flag> flags;
		vk::format format;
		vk::sample_count samples{ 1 };
		vk::load_op load_op {
			vk::attachment_load_op::dont_care
		};
		vk::store_op store_op {
			vk::attachment_store_op::dont_care
		};
		vk::stencil_load_op stencil_load_op {
			vk::attachment_load_op::dont_care
		};
		vk::stencil_store_op stencil_store_op {
			vk::attachment_store_op::dont_care
		};
		vk::initial_layout initial_layout {
			vk::image_layout::undefined
		};
		vk::final_layout final_layout {
			vk::image_layout::undefined
		};
	
		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<vk::format>,
			types::are_may_contain_one_decayed<vk::sample_count>,
			types::are_may_contain_one_decayed<vk::load_op>,
			types::are_may_contain_one_decayed<vk::store_op>,
			types::are_may_contain_one_decayed<vk::stencil_load_op>,
			types::are_may_contain_one_decayed<vk::stencil_store_op>,
			types::are_may_contain_one_decayed<vk::initial_layout>,
			types::are_may_contain_one_decayed<vk::final_layout>
		>::for_types<Args...>
		attachment_description(Args&&... args) {
			format = elements::decayed<vk::format>(args...);
	
			if constexpr(
				types::are_contain_decayed<vk::sample_count>::for_types<Args...>
			) { samples = elements::decayed<vk::sample_count>(args...); }
	
			if constexpr(
				types::are_contain_decayed<vk::load_op>::for_types<Args...>
			) { load_op = elements::decayed<vk::load_op>(args...); }
	
			if constexpr(
				types::are_contain_decayed<vk::store_op>::for_types<Args...>
			) { store_op = elements::decayed<vk::store_op>(args...); }
	
			if constexpr(
				types::are_contain_decayed<
					vk::stencil_load_op
				>::for_types<Args...>
			) {
				stencil_load_op = elements::decayed<
					vk::stencil_load_op
				>(args...);
			}
	
			if constexpr(
				types::are_contain_decayed<
					vk::stencil_store_op
				>::for_types<Args...>
			) {
				stencil_store_op = elements::decayed<
					vk::stencil_store_op
				>(args...);
			}
	
			if constexpr(
				types::are_contain_decayed<
					vk::initial_layout
				>::for_types<Args...>
			) {
				initial_layout = elements::decayed<
					vk::initial_layout
				>(args...);
			}
	
			if constexpr(
				types::are_contain_decayed<vk::final_layout>::for_types<Args...>
			) { final_layout = elements::decayed<vk::final_layout>(args...); }

		} // constructor

	}; // attachment_description

} // vk