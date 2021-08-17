pushd `dirname $0`
cd ..
mkdir -p build
if clang++ -g --config ./compile_flags.txt -lvulkan -o build/$1 demo/$1.cpp
	then ./build/$1
fi
popd
exit 0