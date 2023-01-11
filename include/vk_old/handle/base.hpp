#pragma once

#include "type.hpp"

#include <core/integer.hpp>

namespace vk {

	template<handle_type>
	struct handle_base;

	template<>
	struct handle_base<vk::dispatchable> {
		void* m_value = nullptr;

		auto& value() { return m_value; }
		auto& value() const { return m_value; }

		void reset_value() { value() = nullptr; }
	};

	template<>
	struct handle_base<vk::non_dispatchable> {
		uint64 m_value = 0;

		auto& value() { return m_value; }
		auto& value() const { return m_value; }

		void reset_value() { value() = 0; }
	};

} // vk