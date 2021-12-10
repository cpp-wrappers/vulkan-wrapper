#pragma once

#include <core/integer.hpp>
#include <core/number.hpp>
#include "vk/surface/handle.hpp"
#include "vk/instance/handle.hpp"

namespace platform {
	struct logger {
		void* raw;

		void string(const char*, nuint length) const;

		void operator () (const char*) const;
		void operator () (char) const;

		void new_line() const {
			(*this)('\n');
		}

		template<unsigned_integer I>
		void operator() (I i) const {
			for_each_digit_in_number(number{ i }, base{ 10 }, [this](nuint digit) {
				(*this)(char(digit + '0'));
			});
		}

		void operator() (bool b) const {
			if(b) (*this)("true");
			else (*this)("false");
		}

		template<typename... Args>
		requires(sizeof...(Args) >= 2)
		void operator () (Args... args) {
			( (*this)(args), ... );
		}
	};

	extern logger info;
	extern logger error;

	nuint file_size(const char*);
	void read_file(const char*, char* buff, nuint size);

	nuint required_instance_extension_count();
	const char** get_required_instance_extensions();

	elements::one_of<c_string, vk::surface> try_create_surface(vk::instance);

	bool should_close();
	void begin();
	void end();
}

int entrypoint();