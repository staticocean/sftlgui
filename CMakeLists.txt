cmake_minimum_required(VERSION 3.16)
project(lib_gui CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-write-strings")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-format-security")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-int-to-void-pointer-cast")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-deprecated-declarations")

add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
add_compile_definitions(IMGUI_DEFINE_MATH_OPERATORS)

if (UNIX)

    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DVK_PROTOTYPES")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DVK_PROTOTYPES")

    # GLFW

    # sudo apt install libgtk-3-dev
    # libglfw3-dev

    find_package(Vulkan REQUIRED)
    find_package(glfw3 REQUIRED)
    set(LIBRARIES "glfw;Vulkan::Vulkan")

    # Use vulkan headers from glfw:
    include_directories(${GLFW_DIR}/deps)
    include_directories(${GLEW_INCLUDE_DIRS})

    include_directories(./lib/imgui/backends/)
    include_directories(./lib/imgui/examples/libs/)

    file(GLOB src_imgui
            ./lib/imgui/*.cpp
            ./lib/imgui/backends/imgui_impl_vulkan.cpp
            ./lib/imgui/backends/imgui_impl_glfw.cpp
            )

endif (UNIX)

if (WIN32)
    file(GLOB src_imgui
            ./lib/imgui/*
            ./lib/imgui/backends/imgui_impl_opengl3.cpp
            ./lib/imgui/backends/imgui_impl_glfw.cpp
            ./lib/imgui/backends/gl3w/GL/gl3w.c
            )
endif (WIN32)

file(GLOB src_implot
        ./lib/implot/*
        )

add_subdirectory(./lib/clip/)
add_subdirectory(./lib/nfde/)

add_library(lib_gui ${src_imgui} ${src_implot} ${src_clip} ${src_nfde})

target_include_directories(lib_gui PUBLIC ./)
target_include_directories(lib_gui PUBLIC ./lib/imgui)
target_include_directories(lib_gui PUBLIC ./lib/imgui/backends/glfw/include)
target_include_directories(lib_gui PUBLIC ./lib/imgui/backends/gl3w)
target_include_directories(lib_gui PUBLIC ./lib/implot)
target_include_directories(lib_gui PUBLIC ./lib/clip)
target_include_directories(lib_gui PUBLIC ./lib/nfde/src/include)

if (WIN32)
    target_link_libraries(lib_gui PUBLIC shlwapi)
    target_link_libraries(lib_gui PUBLIC opengl32)
endif(WIN32)

target_link_libraries(lib_gui PUBLIC clip)
target_link_libraries(lib_gui PUBLIC nfd)

if (UNIX)
    target_link_libraries(lib_gui PUBLIC Vulkan::Vulkan)
    target_link_libraries(lib_gui PUBLIC glfw)
endif (UNIX)


