#pragma once 

#include <core/flag_enum.hpp>
#include <core/types/are_exclusively_satsify_predicates.hpp>
#include <core/types/are_contain_type.hpp>
#include <core/wrapper/of.hpp>
#include <core/elements/of_type.hpp>
#include <core/types/count_of_type.hpp>

#include "../../shared/headers.hpp"
#include "../../shared/sample_count.hpp"
#include "../image/format.hpp"
#include "../image/layout.hpp"
#include "attachment_load_op.hpp"
#include "attachment_store_op.hpp"

namespace vk {

	enum class attachment_description_flag {
		may_alias = VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT
	};
	
	struct load_op : wrapper::of<vk::attachment_load_op> {};
	struct store_op : wrapper::of<vk::attachment_store_op> {};
	
	struct stencil_load_op : wrapper::of<vk::attachment_load_op> {};
	struct stencil_store_op : wrapper::of<vk::attachment_store_op> {};
	
	struct attachment_description {
		flag_enum<attachment_description_flag> flags;
		vk::format format;
		vk::sample_count samples{ 1 };
		vk::load_op load_op{ vk::attachment_load_op::dont_care };
		vk::store_op store_op{ vk::attachment_store_op::dont_care };
		vk::stencil_load_op stencil_load_op{ vk::attachment_load_op::dont_care };
		vk::stencil_store_op stencil_store_op{ vk::attachment_store_op::dont_care };
		vk::initial_layout initial_layout { vk::image_layout::undefined };
		vk::final_layout final_layout{ vk::image_layout::undefined };
	
		template<typename... Args>
		requires(
			types::are_exclusively_satsify_predicates<
				types::count_of_type<vk::format>::equals<1>,
				types::count_of_type<vk::sample_count>::less_or_equals<1>,
				types::count_of_type<vk::load_op>::less_or_equals<1>,
				types::count_of_type<vk::store_op>::less_or_equals<1>,
				types::count_of_type<vk::stencil_load_op>::less_or_equals<1>,
				types::count_of_type<vk::stencil_store_op>::less_or_equals<1>,
				types::count_of_type<vk::initial_layout>::less_or_equals<1>,
				types::count_of_type<vk::final_layout>::less_or_equals<1>
			>::for_types_of<Args...>
		)
		attachment_description(Args... args) {
			format = elements::of_type<vk::format&>::for_elements_of(args...);
	
			if constexpr(types::are_contain_type<vk::sample_count>::for_types_of<Args...>)
				samples = elements::of_type<vk::sample_count&>::for_elements_of(args...);
	
			if constexpr(types::are_contain_type<vk::load_op>::for_types_of<Args...>)
				load_op = elements::of_type<vk::load_op&>::for_elements_of(args...);
	
			if constexpr(types::are_contain_type<vk::store_op>::for_types_of<Args...>)
				store_op = elements::of_type<vk::store_op&>::for_elements_of(args...);
	
			if constexpr(types::are_contain_type<vk::stencil_load_op>::for_types_of<Args...>)
				stencil_load_op = elements::of_type<vk::stencil_load_op&>::for_elements_of(args...);
	
			if constexpr(types::are_contain_type<vk::stencil_store_op>::for_types_of<Args...>)
				stencil_store_op = elements::of_type<vk::stencil_store_op&>::for_elements_of(args...);
	
			if constexpr(types::are_contain_type<vk::initial_layout>::for_types_of<Args...>)
				initial_layout = elements::of_type<vk::initial_layout&>::for_elements_of(args...);
	
			if constexpr(types::are_contain_type<vk::final_layout>::for_types_of<Args...>)
				final_layout = elements::of_type<vk::final_layout&>::for_elements_of(args...);
		}
	};

}

static_assert(sizeof(vk::attachment_description) == sizeof(VkAttachmentDescription));