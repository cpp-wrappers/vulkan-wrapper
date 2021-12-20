#pragma once

#include <core/integer.hpp>
#include <core/number.hpp>
#include <core/c_string.hpp>
#include <core/span.hpp>
#include "vk/surface/guard.hpp"
#include "vk/instance/handle.hpp"

namespace platform {
	struct logger {
		void* raw;

		const logger& string(const char*, nuint length) const;

		const logger& operator () (const char*) const;
		const logger& operator () (char) const;

		auto& new_line() const {
			(*this)('\n');
			return *this;
		}

		template<unsigned_integer I>
		auto& operator() (I i) const {
			for_each_digit_in_number(number{ i }, base{ 10 }, [this](nuint digit) {
				(*this)(char(digit + '0'));
			});
			return *this;
		}

		auto& operator() (bool b) const {
			if(b) (*this)("true");
			else (*this)("false");
			return *this;
		}

		template<typename... Args>
		requires(sizeof...(Args) >= 2)
		auto& operator () (Args... args) const {
			( (*this)(args), ... );
			return *this;
		}

		auto& operator() (c_string str) const {
			(*this)(str.begin());
			return *this;
		}
	};

	extern logger info;
	extern logger error;

	nuint file_size(const char*);
	void read_file(const char*, char* buff, nuint size);

	span<vk::extension_name> get_required_instance_extensions();

	vk::surface_guard create_surface(vk::instance);

	bool should_close();
	void begin();
	void end();
}

void entrypoint();