#pragma once

#include <core/handle/guarded_declaration.hpp>

#include "vk/create_or_allocate.hpp"
#include "vk/destroy_or_free.hpp"
#include "vk/handle/base.hpp"

namespace vk {

	template<typename ObjectType>
	class guarded_handle_base {
		handle<ObjectType> m_handle{};

	public:
		using object_type = ObjectType;

		guarded_handle_base() = default;

		guarded_handle_base(handle<ObjectType> handle)
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

		void reset(handle<ObjectType> v = {}) {
			if(handle().value) {
				if constexpr(vk::is_creatable<ObjectType>) {
					((guarded_handle<ObjectType>*)this)->destroy();
				}
				else {
					((guarded_handle<ObjectType>*)this)->free();
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

		const ::handle<ObjectType>& handle() const &  { return m_handle; }
		      ::handle<ObjectType>& handle()       &  { return m_handle; }
		      ::handle<ObjectType>  handle() const && { return m_handle; }
		      ::handle<ObjectType>  handle()       && { return m_handle; }

		/*operator ::handle<ObjectType> () const {
			return handle();
		}*/
	};
}