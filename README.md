
# Homework 02 Solution Set for AERSP424

This repository contains solutions for Homework 02 of the AERSP424 course. Each question is implemented as a separate C++ executable. Below are instructions to build, install, and run the executables.

---

## Prerequisites

Before building and running this project, ensure that the following dependencies are installed on your system:

1. **CMake** (minimum version 3.22)
2. **GLEW** (version 2.2.0 or higher)
3. **GLFW** (installed in the `third_party/glfw` directory)
4. **Matplot++** (installed in the `third_party/matplotplusplus` directory)
5. **OpenGL** (provided by macOS or installed manually)

### Setting Up Dependencies

If GLEW or Matplot++ is installed via Homebrew, ensure the library paths are correctly configured:
```
export DYLD_LIBRARY_PATH=/opt/homebrew/opt/glew/lib:/opt/homebrew/opt/matplotplusplus/lib:$DYLD_LIBRARY_PATH
```
---

## Build Instructions

Follow these steps to build and install the executables:

1. Clone the repository and navigate to the project root directory:
    ```
    cd /path/to/homework02_AERSP424
    ```

2. Create a build directory and configure the project:
    ```
    rm -rf build
    mkdir build
    cd build
    cmake ..
    ```

3. Build the project:
    ```
    make
    ```

4. Install the executables to the `bin` directory:
    ```
    make install
    ```

---

## Running the Executables

After installation, you can run each executable from the `bin` directory.

1. Navigate to the project root:
    ```
    cd /path/to/homework02_AERSP424/build/install/bin
    ./bin/Question1
    ./bin/Question2
    ./bin/Question3
    ```

2. Use the provided scripts to run the executables. These scripts automatically set up the required environment variables.


## Debugging Tips

If you encounter issues when running the executables, follow these steps to debug:

1. Verify the file exists and has correct permissions:
    ```
    ls -l /path/to/homework02_AERSP424/bin/Question1
    ```

2. Check for missing dynamic library dependencies:
    ```
    otool -L /path/to/homework02_AERSP424/bin/Question1
    ```

3. Ensure the environment variable `DYLD_LIBRARY_PATH` is set correctly:
    ```
    export DYLD_LIBRARY_PATH=/opt/homebrew/opt/glew/lib:/opt/homebrew/opt/matplotplusplus/lib:$DYLD_LIBRARY_PATH
    ```

---

## Cleaning Up

To clean the project and remove build artifacts:
```
rm -rf build
```

