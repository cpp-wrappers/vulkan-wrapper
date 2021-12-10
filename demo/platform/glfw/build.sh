while [ $# -gt 0 ]; do
	case $1 in
	--run)
		run=1
		;;
	--sanitize)
		sanitize=1
		;;
	esac

	shift
done

if [ -z $CXX ]; then
	CXX=clang++
fi

declare -a args

args+=(-std=c++20)
args+=(-g)
args+=(-nostdinc++)
args+=(-fmodules)
args+=(-I${root_dir}/../core/include)
args+=(-Xclang -fimplicit-module-maps)
args+=(-I${root_dir}/include)

if [ -v sanitize ]; then
	args+=(-fsanitize=address)
	args+=(-fsanitize=undefined)
fi

if ! $CXX \
	-v \
	-c \
	${args[@]} \
	-o ${platform_dir}/build/platform.o \
	${platform_dir}/platform.cpp

	then 
	exit 1
fi

declare -a libs

if [ $OS == Windows_NT ]; then
	libs+=(-lglfw3)
	libs+=(/c/Windows/System32/vulkan-1.dll)
else
	libs+=(-lglfw)
	libs+=(-lvulkan)
fi

if ! $CXX \
	-v \
	${args[@]} \
	${platform_dir}/build/platform.o \
	-o ${src_dir}/build/${src_name} \
	${src_path} \
	${libs[@]}

	then
	exit 1
fi

if [ -v run ]; then
	pushd ${src_dir}/build
	./${src_name}
	popd
fi