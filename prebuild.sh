pushd `dirname $0`

mkdir -p build

prebuild() {
	if ! $CXX --config ./compile_flags.txt -c \
		-Xclang -emit-module-interface \
		-g \
		-o./build/vk.$1.pcm \
		./include/vk/$1.hpp
		then exit 1;
	fi
}

prebuild result
prebuild extent
prebuild api_version
prebuild application_info
prebuild physical_device_sparse_properties
prebuild physical_device_limits
prebuild physical_device_properties
prebuild queue_family_properties
prebuild physical_device_queue_families_properties_view
prebuild extension_properties
prebuild physical_device_extensions_properties_view
prebuild physical_device
prebuild instance
prebuild format
#prebuild image

popd