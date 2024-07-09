cmake_minimum_required(VERSION 3.10.0)
project(RenderASCII VERSION 0.1.0 LANGUAGES C CXX)

set(OpenCV_DIR "C:/Users/Yusuf/Desktop/Stuff/scripts/opencv/build/x64/vc16/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(RenderASCII main.cpp imageRenderer.cpp imageRenderer.hpp terminalUtils.cpp terminalUtils.hpp)

target_link_libraries(RenderASCII ${OpenCV_LIBS})
