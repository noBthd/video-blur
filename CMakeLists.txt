cmake_minimum_required(VERSION 3.15)
project(video-blur)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_TOOLCHAIN_FILE "/Users/egorkirichenko/.vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")
set(CMAKE_PREFIX_PATH "/Users/egorkirichenko/.vcpkg/vcpkg/installed/arm64-osx")

find_package(OpenCV CONFIG REQUIRED)

add_executable(main 
    src/main.cpp
)

target_link_libraries(main PRIVATE opencv_core opencv_imgcodecs opencv_highgui opencv_core opencv_videoio opencv_objdetect opencv_dnn)


