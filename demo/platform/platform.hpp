#pragma once

#include <core/integer.hpp>
#include <core/number.hpp>
#include "vk/surface/handle.hpp"
#include "vk/instance/handle.hpp"

namespace platform {

	void info(const char* str);
	void error(const char* str);

	inline void info(char ch) {
		char str[2]{ ch, 0 };
		info(str);
	}

	template<unsigned_integer I>
	void info(I i) {
		for_each_digit_in_number(number{ i }, base{ 10 }, [](nuint digit) {
			info(char(digit + '0'));
		});
	}

	inline void info(bool b) {
		if(b) info("true");
		else info("false");vk::surface surface;
	}

	nuint required_instance_extension_count();
	const char** get_required_instance_extensions();

	elements::one_of<c_string, vk::surface> try_create_surface(vk::instance);

	bool should_close();
	void begin();
	void end();

}

int entrypoint();