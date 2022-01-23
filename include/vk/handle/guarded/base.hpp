#pragma once

#include "declaration.hpp"
#include "../../create_or_allocate.hpp"
#include "../../destroy_or_free.hpp"
#include "../../handle/base.hpp"

namespace vk {

	template<typename ObjectType>
	class guarded_handle_base {
		vk::handle<ObjectType> m_handle{};

	public:
		using object_type = ObjectType;

		guarded_handle_base() = default;

		guarded_handle_base(vk::handle<ObjectType> handle)
			: m_handle{ handle }
		{}

		guarded_handle_base(guarded_handle_base&& other)
			: m_handle{ other.m_handle.value }
		{
			other.handle().reset_value();
		}

		void destroy() const requires vk::is_creatable<ObjectType> {
			vk::destroy<ObjectType>(handle());
		}

		void reset(vk::handle<ObjectType> v = {}) {
			if(handle().value) {
				if constexpr(vk::is_creatable<ObjectType>) {
					((vk::guarded_handle<ObjectType>*)this)->destroy();
				}
				else {
					((vk::guarded_handle<ObjectType>*)this)->free();
				}
			}
			handle() = v;
		}

		~guarded_handle_base() {
			reset();
		}

		guarded_handle_base& operator = (guarded_handle_base&& other) {
			reset(other.handle());
			other.handle().reset_value();
			return *this;
		}

		const vk::handle<ObjectType>& handle() const &  { return m_handle; }
		      vk::handle<ObjectType>& handle()       &  { return m_handle; }
		      vk::handle<ObjectType>  handle() const && { return m_handle; }
		      vk::handle<ObjectType>  handle()       && { return m_handle; }

		operator vk::handle<ObjectType> () const {
			return handle();
		}
	};
}