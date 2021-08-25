pushd `dirname $0`
cd ..
mkdir -p build
if clang++ -g --config ./compile_flags.txt -fsanitize=address -fsanitize=undefined -lvulkan $2 -o build/$1 demo/$1.cpp
	then
	cd build
	./$1
fi
popd
exit 0