pushd `dirname $0`

debug=0

while getopts "dn:" opt ; do
	case $opt in
		d ) debug=1 ;;
		n ) name="$OPTARG" ;;
	esac
done

test() {
	name=$1
	echo testing $name

	mkdir -p "build/`dirname $1`"

	if ! $CXX \
		--config ./compile_flags.txt \
		-lvulkan \
		-g \
		-o ./build/$1 \
		./test/$1.cpp
		then
		exit 1;
	fi
	
	if [ $debug -eq 0 ] ; then
		command="./build/$1"
	else 
		command="gdb ./build/$1"
	fi

	$command
	if [ $? -ne 0 ] ; then
		exit 1
	fi
}

if [ ! -z $name ]; then
	test $name
	exit 0
fi

test api_version
test application_info
test device_queue_family_create_info
test instance

popd