pushd `dirname $0`

mkdir -p build

prebuild() {
	if ! $CXX --config ./compile_flags.txt -c \
		-Xclang -emit-module-interface \
		-o./build/vk.$1.pcm \
		./include/vk/$1.hpp
		then exit 1;
	fi
}

prebuild api_version
prebuild application_info
prebuild physical_device
prebuild instance

popd