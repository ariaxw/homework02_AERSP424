#!/bin/sh
current_directory="$(cd "$(dirname "$0")" && pwd)"
project_root_dir=$current_directory

# if on MacOS, you will need to install cmake, python, numpy, xcode-tools

echo "Hello Friend! Let's try and build this application together :D"

mkdir -p ${project_root_dir}/third_party
cd ${project_root_dir}/third_party
#compile MATPLOTPLUSPLUS
if [ ! -d "matplotplusplus" ]; then
    git clone https://github.com/alandefreitas/matplotplusplus
    cd ${project_root_dir}/third_party/matplotplusplus
    rm -rf build install
    mkdir -p build && mkdir -p install && cd build
    cmake -DCMAKE_INSTALL_PREFIX=${project_root_dir}/third_party/matplotplusplus/install -DCMAKE_BUILD_TYPE=Release ..
    cmake --build . -j 4
    cmake --install .
fi

cd ${project_root_dir}/third_party
if [ ! -d "glew" ]; then
    git clone https://github.com/Perlmint/glew-cmake.git glew
    cd ${project_root_dir}/third_party/glew
    rm -rf build install
    mkdir -p build && mkdir -p install && cd build
    cmake -DCMAKE_INSTALL_PREFIX=${project_root_dir}/third_party/glew/install -DCMAKE_BUILD_TYPE=Release ..
    cmake --build . -j 4
    cmake --install .
fi

cd ${project_root_dir}/third_party
if [ ! -d "glfw" ]; then
    git clone https://github.com/glfw/glfw.git glfw
    cd ${project_root_dir}/third_party/glfw
    rm -rf build install
    mkdir -p build && mkdir -p install && cd build
    cmake -DCMAKE_INSTALL_PREFIX=${project_root_dir}/third_party/glfw/install -DCMAKE_BUILD_TYPE=Release ..
    cmake --build . -j 4
    cmake --install .
fi


# compile the rest of the application
cd ${project_root_dir}

# remove the build directory that has the current code in it
echo "deleting the BUILD directory"
rm -rf ${project_root_dir}/build
rm -rf ${project_root_dir}/install

echo "make a new BUILD directory to start the compiling process"
mkdir -p ${project_root_dir}/build
cd ${project_root_dir}/build

echo "cmake engage!"
cmake ..

echo "convert this to an executable application -- let's go!!"
cmake --build . -j 4
cmake --install .
cpack
cd ${project_root_dir}
echo "declare success -- hooray!"

if [ -f "./build/homework02_AERSP424" ]; then
    echo "Running the executable with default parameters"
    mkdir -p ${project_root_dir}/results
    ./build/homework02_AERSP424 -c config.inp > results/results.txt 2>&1
    echo "Execution completed. Check the results in the results directory."
else
    echo "Executable not found. Build might have failed."
fi



