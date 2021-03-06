#pragma once

#include "handle.hpp"
#include "attachment_description.hpp"
#include "create_info.hpp"

#include "../create_or_allocate.hpp"
#include "../device/handle.hpp"
#include "../function.hpp"

#include <core/meta/elements/pass_not_satisfying_type_predicate.hpp>

extern "C" VK_ATTR int32 VK_CALL vkCreateRenderPass(
	handle<vk::device>                 device,
	const vk::render_pass_create_info* create_info,
	const void*                        allocator,
	handle<vk::render_pass>*           render_pass
);

namespace vk {

	template<>
	struct vk::create_t<vk::render_pass> {

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<handle<vk::device>>,
			types::are_contain_range_of<vk::subpass_description>,
			types::are_may_contain_range_of<vk::subpass_dependency>,
			types::are_may_contain_range_of<vk::attachment_description>
		>::for_types<Args...>
		vk::expected<handle<vk::render_pass>>
		operator () (Args&&... args) const {
			vk::render_pass_create_info ci{};

			auto& subpass_descriptions {
				elements::range_of<vk::subpass_description>(args...)
			};

			ci.subpass_count = (uint32) subpass_descriptions.size();
			ci.subpasses = subpass_descriptions.data();

			if constexpr (
				types::are_contain_range_of<
					vk::subpass_dependency
				>::for_types<Args...>
			) {
				auto& subpass_dependencies {
					elements::range_of<vk::subpass_dependency>(args...)
				};

				ci.dependency_count = (uint32) subpass_dependencies.size();
				ci.dependencies = subpass_dependencies.data();
			}

			if constexpr (
				types::are_contain_range_of<
					vk::attachment_description
				>::for_types<Args...>
			) {
				auto& attachment_descriptions {
					elements::range_of<vk::attachment_description>(args...)
				};

				ci.attachment_count = (uint32) attachment_descriptions.size();
				ci.attachments = attachment_descriptions.data();
			}

			auto device = elements::decayed<handle<vk::device>>(args...);

			handle<vk::render_pass> render_pass;

			vk::result result {
				vkCreateRenderPass(
					device,
					&ci,
					nullptr,
					&render_pass
				)
			};

			if(result.error()) return result;

			return render_pass;

		} // operator ()

		template<typename... Args>
		requires types::are_exclusively_satisfying_predicates<
			types::are_contain_one_decayed<handle<vk::device>>,
			types::are_contain_one_decayed<vk::subpass_description>,
			types::are_may_contain_range_of<vk::subpass_dependency>,
			types::are_may_contain_range_of<vk::attachment_description>
		>::for_types<Args...>
		vk::expected<handle<vk::render_pass>>
		operator () (Args&&... args) const {
			auto subpass = elements::decayed<vk::subpass_description>(args...);

			return elements::pass_not_satisfying_type_predicate<
				type::is_decayed<vk::subpass_description>
			>(
				array{ subpass },
				forward<Args>(args)...
			)( create_t{} );
		}

	}; // create_t<render_pass>

} // vk