#pragma once

#include <optional>

#include <core/tuple.hpp>
#include <core/storage.hpp>
#include <vulkan/vulkan_core.h>

#include "headers.hpp"
#include "device_create_info.hpp"
#include "result.hpp"
#include "queue_family_index.hpp"
#include "command_pool.hpp"
#include "command_pool_create_info.hpp"
#include "shader_module.hpp"
#include "shader_module_create_info.hpp"
#include "render_pass.hpp"
#include "render_pass_create_info.hpp"
#include "attachment_description.hpp"
#include "subpass_dependency.hpp"
#include "subpass_description.hpp"
#include "framebuffer_create_info.hpp"
#include "extent.hpp"
#include "framebuffer.hpp"
#include "swapchain.hpp"
#include "swapchain_create_info.hpp"
#include "color_space.hpp"
#include "image/usage.hpp"
#include "sharing_mode.hpp"
#include "surface.hpp"
#include "image/view_create_info.hpp"
#include "image/component_mapping.hpp"
#include "image/subresource_range.hpp"
#include "vk/image_view.hpp"

namespace vk {

struct device {
	device() = delete;
	device(const device&) = delete;

	template<typename... Args>
	requires(
		types::of<Args...>::template count_of_same_as_type<vk::queue_family_index> == 1 &&
		(
			types::of<Args...>::size - 1
			-
			types::of<Args...>::template count_of_same_as_type<vk::command_pool_create_flag>
		) == 0
	)
	vk::command_pool& create_command_pool(Args... args) const {
		vk::command_pool_create_info ci{};

		tuple{ args... }
			.get([&](vk::queue_family_index i) {
				ci.queue_family_index = i;
			})
			.get([&](vk::command_pool_create_flag f) {
				ci.flags.set(f);
			});

		vk::command_pool* command_pool;

		vk::throw_if_error(
			vkCreateCommandPool(
				(VkDevice) this,
				(VkCommandPoolCreateInfo*) &ci,
				nullptr,
				(VkCommandPool*) &command_pool
			)
		);

		return *command_pool;
	}

	template<typename... Args>
	requires(
		types::of<Args...>::template count_of_same_as_type<code_size> == 1 &&
		types::of<Args...>::template count_of_same_as_type<code> == 1 &&
		types::of<Args...>::size == 2
	)
	vk::shader_module& create_shader_module(Args&&... args) const {
		vk::shader_module_create_info ci{};

		tuple{ args... }
			.get([&](vk::code_size cs) {
				ci.code_size = cs;
			})
			.get([&](vk::code c) {
				ci.code = c;
			});
		
		vk::shader_module* shader_module;

		vk::throw_if_error(
			vkCreateShaderModule(
				(VkDevice) this,
				(VkShaderModuleCreateInfo*) &ci,
				nullptr,
				(VkShaderModule*) &shader_module
			)
		);

		return *shader_module;
	}

	template<typename... Args>
	requires(
		types::of<Args...>::template count_of_same_as_type<vk::subpass_description> > 0 &&
		types::of<Args...>::template erase_same_as_one_of_types<
			vk::attachment_description,
			vk::subpass_description,
			vk::subpass_dependency
		>::empty
	)
	vk::render_pass& create_render_pass(Args&&... args) const {
		using Types = types::of<Args...>;

		vk::render_pass_create_info ci{};

		ci.attachment_count = Types::template count_of_same_as_type<vk::attachment_description>;
		storage_for<vk::attachment_description> adss[ci.attachment_count];
		auto ads = (vk::attachment_description*)adss;
		std::size_t adi = 0;

		ci.subpass_count = Types::template count_of_same_as_type<vk::subpass_description>;
		storage_for<vk::subpass_description> sdss[ci.subpass_count];
		auto sds = (vk::subpass_description*) sdss;
		std::size_t sdi = 0;

		ci.dependency_count = Types::template count_of_same_as_type<vk::subpass_dependency>;
		storage_for<vk::subpass_dependency> sdpss[ci.dependency_count];
		auto sdps = (vk::subpass_dependency*) sdpss;
		std::size_t sdpi = 0;

		tuple{ args... }
			.get([&](vk::attachment_description ad) {
				ads[adi++] = ad;
			})
			.get([&](vk::subpass_description sd) {
				sds[sdi++] = sd;
			})
			.get([&](vk::subpass_dependency sdp) {
				sdps[sdpi++] = sdp;
			});
		ci.attachments = ads;
		ci.subpasses = sds;
		ci.dependencies = sdps;
		
		vk::render_pass* render_pass;

		vk::throw_if_error(
			vkCreateRenderPass(
				(VkDevice) this,
				(VkRenderPassCreateInfo*) &ci,
				nullptr,
				(VkRenderPass*) &render_pass
			)
		);

		return *render_pass;
	}

	template<typename... Args>
	requires(
		types::of<Args...>::template count_of_same_as_type<vk::render_pass&> == 1 &&
		types::of<Args...>::template count_of_remove_cvref_same_as_type<vk::attachment_count> == 1 &&
		types::of<Args...>::template count_of_remove_cvref_same_as_type<vk::attachments> == 1 &&
		types::of<Args...>::template count_of_remove_cvref_same_as_type<vk::extent<3>> == 1 &&
		types::of<Args...>::template erase_same_as_one_of_types<
			vk::render_pass&, vk::attachment_count, vk::attachments, vk::extent<3>
		>::empty
	)
	vk::framebuffer& create_framebuffer(Args&&... args) const {
		vk::framebuffer_create_info ci{};

		tuple{ args... }
			.get([&](vk::render_pass& rp) {
				ci.render_pass = &rp;
			})
			.get([&](vk::attachment_count ac) {
				ci.attachment_count = ac;
			})
			.get([&](vk::attachments as) {
				ci.attachments = as;
			})
			.get([&](vk::extent<3> e) {
				ci.width = e.width();
				ci.height = e.height();
				ci.layers = e.depth();
			})
		;

		vk::framebuffer* framebuffer;
		vk::throw_if_error(
			vkCreateFramebuffer(
				(VkDevice) this,
				(VkFramebufferCreateInfo*) &ci,
				nullptr,
				(VkFramebuffer*) &framebuffer
			)
		);

		return *framebuffer;
	}

	template<typename... Args>
	requires(
		types::of<Args...>::template count_of_same_as_type<vk::surface&> == 1 &&
		types::of<Args...>::template count_of_remove_cvref_same_as_type<vk::min_image_count> == 1 &&
		types::of<Args...>::template count_of_remove_cvref_same_as_type<vk::format> == 1 &&
		types::of<Args...>::template count_of_remove_cvref_same_as_type<vk::color_space> == 1 &&
		types::of<Args...>::template count_of_remove_cvref_same_as_type<vk::extent<2>> == 1 &&
		types::of<Args...>::template count_of_remove_cvref_same_as_type<vk::image_usage> == 1 &&
		types::of<Args...>::template count_of_remove_cvref_same_as_type<vk::sharing_mode> == 1 &&
		types::of<Args...>::template count_of_remove_cvref_same_as_type<vk::queue_family_index_count> == 1 &&
		types::of<Args...>::template count_of_remove_cvref_same_as_type<vk::queue_family_indices> == 1 &&
		types::of<Args...>::template count_of_remove_cvref_same_as_type<vk::present_mode> == 1 &&
		types::of<Args...>::template count_of_remove_cvref_same_as_type<vk::clipped> == 1 &&
		types::of<Args...>::template erase_remove_cvref_same_as_one_of_types<
			vk::swapchain_create_flag, vk::surface, vk::min_image_count, vk::format,
			vk::color_space, vk::extent<2>, vk::image_array_layers, vk::image_usage,
			vk::sharing_mode, vk::queue_family_index_count, vk::queue_family_indices,
			vk::surface_transform, vk::composite_alpha,
			vk::present_mode, vk::clipped, vk::swapchain
		>::empty
	)
	vk::swapchain& create_swapchain(Args&&... args) {
		vk::swapchain_create_info ci{};

		tuple<Args...>{ std::forward<Args>(args)... }
			.get([&](vk::swapchain_create_flag f) { ci.flags.set(f); })
			.get([&](vk::surface& s) { ci.surface = &s; })
			.get([&](vk::min_image_count c) { ci.min_image_count = c; })
			.get([&](vk::format f) { ci.format = f; })
			.get([&](vk::color_space c) { ci.color_space = c; })
			.get([&](vk::extent<2> e) { ci.extent = e; })
			.get([&](vk::image_array_layers l) { ci.image_array_layers = l; })
			.get([&](vk::image_usage u) { ci.usage = u; })
			.get([&](vk::sharing_mode sm) { ci.sharing_mode = sm; })
			.get([&](vk::queue_family_index_count c) { ci.queue_family_index_count = c; })
			.get([&](vk::queue_family_indices i) { ci.queue_family_indices = i; })
			.get([&](vk::surface_transform f) { ci.pre_transform = f; })
			.get([&](vk::composite_alpha f) { ci.composite_alpha = f; })
			.get([&](vk::present_mode m) { ci.present_mode = m; })
			.get([&](vk::clipped c) { ci.clipped = c; })
			.get([&](vk::swapchain& s) { ci.swapchain = &s; })
		;

		vk::swapchain* swapchain;

		vk::throw_if_error(
			vkCreateSwapchainKHR(
				(VkDevice) this,
				(VkSwapchainCreateInfoKHR*) &ci,
				nullptr,
				(VkSwapchainKHR*) &swapchain
			)
		);

		return *swapchain;
	}

	template<typename... Args>
	requires(
		types::of<Args...>::template count_of_same_as_type<vk::image&> == 1 &&
		types::of<Args...>::template count_of_remove_cvref_same_as_type<vk::image_view_type> == 1 &&
		types::of<Args...>::template count_of_remove_cvref_same_as_type<vk::format> == 1 &&
		types::of<Args...>::template count_of_remove_cvref_same_as_type<vk::component_mapping> == 1 &&
		types::of<Args...>::template count_of_remove_cvref_same_as_type<vk::image_subresource_range> == 1 &&
		types::of<Args...>::template erase_remove_cvref_same_as_one_of_types<
			vk::image_view_create_flag, vk::image_view_type, vk::format,
			vk::component_mapping, vk::image_subresource_range
		>::template erase_types<vk::image&>::empty
	)
	vk::image_view& create_image_view(Args&&... args) const {
		vk::image* image;
		vk::image_view_type image_view_type;
		vk::format format;
		std::optional<vk::component_mapping> component_mapping;
		std::optional<vk::image_subresource_range> image_subresource_range;

		tupe<Args...>(std::forward<Args...>(args...))
			.get([&](vk::image& v){ image = &v; })
			.get([&](vk::image_view_type v){ image_view_type = v; })
			.get([&](vk::format v){ format = v; })
			.get([&](vk::component_mapping v){ component_mapping.emplace(v); })
			.get([&](vk::image_subresource_range v){ image_subresource_range.emplace(v); })
		;

		vk::image_view_create_info ci {
			.image = *image,
			.view_type = image_view_type,
			.format = format,
			.components = component_mapping.value(),
			.subresource_range = image_subresource_range.value()
		};

		vk::image_view* image_view;

		vk::throw_if_error(
			vkCreateImageView(
				(VkDevice) this,
				(VkImageViewCreateInfo*) &ci,
				nullptr,
				(VkImageView*) &image_view
			)
		);

		return *image_view;
	}

};

}