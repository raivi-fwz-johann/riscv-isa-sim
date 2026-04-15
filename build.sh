#!/bin/sh

set -eu

export PATH=/work/tools/gcc-10.3.0/bin:$PATH
export LD_LIBRARY_PATH=/work/tools/gcc-10.3.0/lib64${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}

if command -v nproc >/dev/null 2>&1; then
  build_jobs=${BUILD_JOBS:-$(nproc)}
elif command -v getconf >/dev/null 2>&1; then
  build_jobs=${BUILD_JOBS:-$(getconf _NPROCESSORS_ONLN)}
else
  build_jobs=${BUILD_JOBS:-8}
fi

root_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
build_dir="$root_dir/build"
install_dir="$root_dir/libs"

rm -rf "$build_dir"
mkdir -p "$build_dir" "$install_dir/lib"

cd "$build_dir"
echo "start configuring ..."
"$root_dir/configure" \
  --prefix="$install_dir" \
  --without-boost \
  --without-boost-asio \
  --without-boost-regex

echo "start make ..."
make -j"$build_jobs"

echo "start install ..."
g++ -v
make install

for archive in libriscv.a libfdt.a libfesvr.a libdisasm.a libsoftfloat.a; do
  install -m 644 "$archive" "$install_dir/lib/"
done

rm -f "$install_dir/lib/libriscv.so" "$install_dir/lib/libsoftfloat.so"
