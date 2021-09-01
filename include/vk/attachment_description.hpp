#pragma once 

#include "headers.hpp"
#include <core/flag_enum.hpp>
#include "format.hpp"
#include "sample_count.hpp"
#include "attachment_load_op.hpp"
#include "attachment_store_op.hpp"
#include "image_layout.hpp"
#include <core/types.hpp>
#include <core/named.hpp>
#include <core/tuple.hpp>

namespace vk {

enum class attachment_description_flag {
	may_alias = VK_ATTACHMENT_DESCRIPTION_MAY_ALIAS_BIT
};

struct load_op : named<vk::attachment_load_op> {};
struct store_op : named<vk::attachment_store_op> {};

struct stencil_load_op : named<vk::attachment_load_op> {};
struct stencil_store_op : named<vk::attachment_store_op> {};

struct initial_layout : named<vk::image_layout> {};
struct final_layout : named<vk::image_layout> {};

class attachment_description {
	flag_enum<attachment_description_flag> flags;
	vk::format format;
	vk::sample_count samples{ 1 };
	vk::load_op load_op;
	vk::store_op store_op;
	vk::stencil_load_op stencil_load_op;
	vk::stencil_store_op stencil_store_op;
	vk::initial_layout initial_layout;
	vk::final_layout final_layout;

	attachment_description() = default;

public:

	attachment_description(const attachment_description&) = default;
	attachment_description(attachment_description&) = default;
	attachment_description(attachment_description&&) = default;
	attachment_description& operator = (const attachment_description&) = default;

	// it smells (bad)
	template<typename... Args>
	requires(
		types::of<Args...>::template count_of_type<vk::format> == 1 &&
		types::of<Args...>::template count_of_type<vk::sample_count> <= 1 &&
		types::of<Args...>::template count_of_type<vk::load_op> == 1 &&
		types::of<Args...>::template count_of_type<vk::store_op> == 1 &&
		types::of<Args...>::template count_of_type<vk::stencil_load_op> == 1 &&
		types::of<Args...>::template count_of_type<vk::stencil_store_op> == 1 &&
		types::of<Args...>::template count_of_type<vk::initial_layout> == 1 &&
		types::of<Args...>::template count_of_type<vk::final_layout> == 1 &&
		types::of<Args...>::template erase_types<
			vk::format, vk::sample_count, vk::load_op, vk::store_op,
			vk::stencil_load_op, vk::stencil_store_op, vk::initial_layout, vk::final_layout
		>::empty
	)
	attachment_description(Args&&... args) {
		tuple{ args... }
			.get([&](vk::format f) { format = f; })
			.get([&](vk::sample_count sc) { samples = sc; })
			.get([&](vk::load_op op) { load_op = op; })
			.get([&](vk::store_op op) { store_op = op; })
			.get([&](vk::stencil_load_op op) { stencil_load_op = op; })
			.get([&](vk::stencil_store_op op) { stencil_store_op = op; })
			.get([&](vk::initial_layout il) { initial_layout = il; })
			.get([&](vk::final_layout fl) { final_layout = fl; })
		;
	}
};

}

static_assert(sizeof(vk::attachment_description) == sizeof(VkAttachmentDescription));