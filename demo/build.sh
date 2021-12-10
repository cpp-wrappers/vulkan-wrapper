if [ $1 != --platform ]; then
	echo "first argument is platform"
	exit 1
fi

shift
platform=$1
shift

src_path=`realpath ${BASH_SOURCE[1]}`
echo "src_path: ${src_path}"
src_dir=`dirname ${src_path}`
src_base=`basename ${src_path}`
src_name=${src_base%.*}

script_path=`realpath ${BASH_SOURCE[0]}`
echo "script_path: ${script_path}"
script_dir=`dirname ${script_path}`

root_dir=`realpath ${script_dir}/../`

platform_dir=${script_dir}/platform/${platform}

if ! [ -d ${platform_dir} ]; then
	echo "platform doesn't exist"
	exit 1;
fi

platform_path=${platform_dir}/build.sh

echo "building for ${platform}"
mkdir -p "${platform_dir}/build"
mkdir -p "${src_dir}/build"

. ${platform_path} $@