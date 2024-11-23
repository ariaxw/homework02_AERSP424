#!/bin/bash
current_directory="$(cd "$(dirname "$0")" && pwd)"
project_root_dir=$current_directory

CMAKE_GENERATOR_OPTIONS=-G"Visual Studio 17 2022"
#CMAKE_GENERATOR_OPTIONS=-G"Visual Studio 16 2019"
#CMAKE_GENERATOR_OPTIONS=-G"Visual Studio 15 2017 Win64"
#CMAKE_GENERATOR_OPTIONS=(-G"Visual Studio 16 2019" -A x64)  # CMake 3.14+ is required

mkdir -p ${project_root_dir}/third_party
# compile opencv
cd ${project_root_dir}/third_party
if [ ! -d "opencv" ]; then
	git clone --depth 1 https://github.com/opencv/opencv.git
	echo "fix for opencv not updating their code properly ..."
	line="CV_LOG_WARNING(\"Save dialog requires enabled 'imgcodecs' module.\");"
	rep="CV_LOG_WARNING(NULL, \"Save dialog requires enabled 'imgcodecs' module.\");"
	sed -i "s/${line}/${rep}/g" opencv/modules/highgui/src/window_w32.cpp

	git clone --depth 1 https://github.com/opencv/opencv_contrib.git
fi

cd ${project_root_dir}/third_party
if [ ! -d "build_opencv" ]; then
	# do the build process
	myRepo=$(pwd)
	mkdir -p build_opencv
	pushd build_opencv
	CMAKE_OPTIONS=(-DBUILD_PERF_TESTS:BOOL=OFF -DBUILD_TESTS:BOOL=OFF -DBUILD_DOCS:BOOL=OFF -DWITH_CUDA:BOOL=OFF -DBUILD_EXAMPLES:BOOL=OFF -DINSTALL_CREATE_DISTRIB:BOOL=ON -DBUILD_SHARED_LIBS:BOOL=OFF -DBUILD_LIST=core,highgui -DBUILD_opencv_imgcodecs:BOOL=ON -DBUILD_opencv_world:BOOL=OFF -DBUILD_opencv_highgui:BOOL=ON -DBUILD_opencv_core:BOOL=ON)
	set -x
	cmake "${CMAKE_GENERATOR_OPTIONS[@]}" "${CMAKE_OPTIONS[@]}" -DOPENCV_EXTRA_MODULES_PATH="$project_root_dir"/third_party/opencv_contrib/modules "$project_root_dir"/third_party/opencv
	echo "************************* $Source_DIR -->debug"
	cmake --build . --config debug
	# echo "************************* $Source_DIR -->release"
	#cmake --build .  --config release
	#cmake --build .  --target install --config release
	cmake --build . --target install --config debug
	popd
fi

# echo "********************"
# echo "if you get a "
# echo ">  LINK : fatal error LNK1104: cannot open file '<root>\third_party\build_opencv\lib\Debug\opencv_highgui490d.lib'"
# echo "error, then OpenCV has still not fixed their codebase 🙄"
# echo "to fix this:"
# echo " (1) open <root>\third_party\build_opencv\modules\highgui\opencv_highgui.sln"
# echo " (2) change line 2194 of \"windows_32.cpp\"   in the \"modules\opencv_highgui\src\windows_32.cpp\" project"
# echo '     CV_LOG_WARNING(NULL, "Save dialog requires enabled 'imgcodecs' module.");'
# echo "the CV_LOG_WARNING(NULL, ...) has been a bug for a while now"
# echo " (3) right-click the opencv_highgui project -> Build"
# echo "that will fix it up just fine!"
# echo "********************"
# echo
# echo

cd ${project_root_dir}
rm -rf build
mkdir -p build && cd build

cmake ..
cmake --build . -j 4
cmake --build . --target install --config debug
./Debug/hw2
