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

declare -a args

args+=(-g)
args+=("--config ${root_dir}/compile_flags.txt")

if [ -v sanitize ]; then
	args+=(-fsanitize=address)
	args+=(-fsanitize=undefined)
fi

if [ -z $CXX ]; then
	CXX=clang++
fi

if ! $CXX \
	-c \
	${args[@]} \
	-o ${platform_dir}/build/platform.o \
	${platform_dir}/platform.cpp

	then
	exit 1
fi

if ! $CXX \
	${args[@]} \
	-lvulkan -lglfw \
	${platform_dir}/build/platform.o \
	-o ${src_dir}/build/${src_name} \
	${src_path}

	then
	exit 1
fi

if [ -v run ]; then
	pushd ${src_dir}/build
	./${src_name}
	popd
fi