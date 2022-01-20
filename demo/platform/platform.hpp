#pragma once

#include <core/integer.hpp>
#include <core/number.hpp>
#include <core/c_string.hpp>
#include <core/span.hpp>

#include "vk/objects/instance/handle.hpp"
#include "vk/objects/instance/guarded_handle.hpp"
#include "vk/objects/instance/layer_properties.hpp"
#include "vk/objects/instance/extension_properties.hpp"
#include "vk/objects/surface/guarded_handle.hpp"
#include "vk/objects/debug/report/callback/create.hpp"

void entrypoint();

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
	void read_file(const char*, span<char> buffer);

	struct image_info {
		uint32 width;
		uint32 height;
		nuint size;
	};

	image_info read_image_info(const char* path);

	void read_image_data(const char* path, span<char> buffer);

	span<vk::extension_name> get_required_instance_extensions();

	vk::guarded_handle<vk::surface> create_surface(vk::handle<vk::instance>);

	inline uint32 debug_report(
		flag_enum<vk::debug_report_flag>, vk::debug_report_object_type, uint64, nuint,
		int32, c_string, c_string message, void*
	) {
		platform::info("[vk] ", message).new_line();
		return 0;
	}

	inline vk::handle<vk::instance> create_instance() {
		span required_extensions = platform::get_required_instance_extensions();

		vk::layer_name validation_layer_name{ "VK_LAYER_KHRONOS_validation" };
		bool validation_layer_is_supported = vk::is_instance_layer_supported(validation_layer_name);

		span<vk::layer_name> layers{ validation_layer_is_supported ? &validation_layer_name : nullptr, validation_layer_is_supported ? 1u : 0u };

		vk::extension_name extensions_storage[required_extensions.size() + 1]; // TODO
		span extensions{ extensions_storage, required_extensions.size() + 1 };

		nuint i = 0;
		for(; i < required_extensions.size(); ++i) extensions[i] = required_extensions[i];
		vk::extension_name debug_report_extension_name = { "VK_EXT_debug_report" };
		extensions[i] = debug_report_extension_name;

		vk::handle<vk::instance> instance = vk::create<vk::instance>(layers, extensions);

		if(vk::is_instance_extension_supported(debug_report_extension_name)) {
			instance.create<vk::debug_report_callback>(
				vk::debug_report_flags{ vk::debug_report_flag::error, vk::debug_report_flag::warning, vk::debug_report_flag::information },
				platform::debug_report 
			);
		}

		return instance;
	}

	inline vk::guarded_handle<vk::surface> create_surface(const vk::guarded_handle<vk::instance>& instance) {
		return create_surface(instance.handle());
	}

	inline vk::guarded_handle<vk::shader_module> read_shader_module(const vk::guarded_handle<vk::device>& device, const char* path) {
		auto size = platform::file_size(path);
		char src[size];
		platform::read_file(path, span{ src, size });
		return device.create_guarded<vk::shader_module>(vk::code_size{ (uint32) size }, vk::code{ (uint32*) src } );
	}

	bool should_close();
	void begin();
	void end();
}