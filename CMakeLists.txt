cmake_minimum_required(VERSION 3.16)
project(lib_gui CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format-security")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-int-to-void-pointer-cast")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")

add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
add_compile_definitions(IMGUI_DEFINE_MATH_OPERATORS)

file(GLOB src_imgui
        ./lib/imgui/*
        ./lib/imgui/backends/imgui_impl_opengl3.cpp
        ./lib/imgui/backends/imgui_impl_glfw.cpp
        ./lib/imgui/backends/gl3w/GL/gl3w.c
        )

file(GLOB src_implot
        ./lib/implot/*
        )

file(GLOB src_clip
        ./lib/clip/clip.cpp
        ./lib/clip/image.cpp
        ./lib/clip/clip_win.cpp
        )

file(GLOB src_nfde
        ./lib/nfde/nfd_win.cpp
        )

add_library(lib_gui ${src_imgui} ${src_implot} ${src_clip} ${src_nfde})

target_include_directories(lib_gui PUBLIC ./)
target_include_directories(lib_gui PUBLIC ./lib/imgui)
target_include_directories(lib_gui PUBLIC ./lib/imgui/backends/glfw/include)
target_include_directories(lib_gui PUBLIC ./lib/imgui/backends/gl3w)
target_include_directories(lib_gui PUBLIC ./lib/implot)
target_include_directories(lib_gui PUBLIC ./lib/clip)
target_include_directories(lib_gui PUBLIC ./lib/nfde)

target_link_libraries(lib_gui PUBLIC shlwapi)
target_link_libraries(lib_gui PUBLIC opengl32)
target_link_libraries(lib_gui PUBLIC ${CMAKE_CURRENT_LIST_DIR}/lib/imgui/backends/glfw/lib-vc2010-64/glfw3.lib )

