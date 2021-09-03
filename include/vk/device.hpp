#pragma once

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

		VkCommandPool command_pool;

		vk::throw_if_error(
			vkCreateCommandPool(
				(VkDevice)this,
				(VkCommandPoolCreateInfo*)&ci,
				nullptr,
				&command_pool
			)
		);

		return *((vk::command_pool*)command_pool);
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
		
		VkShaderModule shader_module;

		vk::throw_if_error(
			vkCreateShaderModule(
				(VkDevice)this,
				(VkShaderModuleCreateInfo*)&ci,
				nullptr,
				&shader_module
			)
		);

		return *((vk::shader_module*)shader_module);
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
		
		VkRenderPass render_pass;

		vk::throw_if_error(
			vkCreateRenderPass(
				(VkDevice)this,
				(VkRenderPassCreateInfo*)&ci,
				nullptr,
				&render_pass
			)
		);

		return *((vk::render_pass*)render_pass);
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

		VkFramebuffer framebuffer;
		vk::throw_if_error(
			vkCreateFramebuffer(
				(VkDevice)this,
				(VkFramebufferCreateInfo*)&ci,
				nullptr,
				&framebuffer
			)
		);

		return *((vk::framebuffer*)framebuffer);
	}

};

}