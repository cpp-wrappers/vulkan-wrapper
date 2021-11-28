if [ $1 != --platform ]; then
	echo "first argument is platform"
	exit 1
fi

shift
platform=$1
shift

src_path=`realpath ${BASH_SOURCE[1]}`
src_dir=`dirname ${src_path}`
src_base=`basename ${src_path}`
src_name=${src_base%.*}

script_path=`realpath ${BASH_SOURCE[0]}`
script_dir=`dirname ${script_path}`

root_dir=`realpath ${script_dir}/../`

platform_dir=${script_dir}/platform/${platform}
platform_path=${platform_dir}/build.sh

echo "building for ${platform}"
mkdir -p "${platform_dir}/build"
mkdir -p "${src_dir}/build"

. ${platform_path} $@