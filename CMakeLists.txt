cmake_minimum_required(VERSION 3.16)
project(sftlgui CXX)

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

    # Use vulkan headers from glfw:

    include_directories(./imgui/backends/)
    include_directories(./imgui/examples/libs/)

    file(GLOB src_imgui
            ./imgui/*.cpp
            ./imgui/backends/imgui_impl_vulkan.cpp
            ./imgui/backends/imgui_impl_glfw.cpp
            )

endif (UNIX)

if (WIN32)

    file(GLOB src_imgui
            ./imgui/*.cpp
            ./imgui/backends/imgui_impl_opengl3.cpp
            ./imgui/backends/imgui_impl_glfw.cpp
            ./imgui/examples/libs/gl3w/GL/gl3w.c
            )

endif (WIN32)

file(GLOB src_implot
        ./implot/*.cpp
        )

add_subdirectory(./clip/)
add_subdirectory(./nfde/)

add_library(sftlgui ${src_imgui} ${src_implot} ${src_clip} ${src_nfde})

target_include_directories(sftlgui PUBLIC ./)
target_include_directories(sftlgui PUBLIC ./imgui)
target_include_directories(sftlgui PUBLIC ./imgui/backends/glfw/include)
target_include_directories(sftlgui PUBLIC ./imgui/backends/gl3w)
target_include_directories(sftlgui PUBLIC ./implot)
target_include_directories(sftlgui PUBLIC ./clip)
target_include_directories(sftlgui PUBLIC ./nfde/src/include)

if (WIN32)
    target_link_libraries(sftlgui PUBLIC shlwapi)
    target_link_libraries(sftlgui PUBLIC opengl32)
    target_link_libraries(sftlgui PUBLIC gdi32)
    target_link_libraries(sftlgui PUBLIC shell32)
    target_link_libraries(sftlgui PUBLIC glu32)

    find_library(lib_glfw3 glfw3 HINTS imgui/examples/libs/glfw/lib-vc2010-64)
    target_link_libraries(sftlgui PUBLIC ${lib_glfw3})

    target_include_directories(sftlgui PUBLIC ./imgui/backends/)
    target_include_directories(sftlgui PUBLIC ./imgui/examples/libs/glfw/include)
    target_include_directories(sftlgui PUBLIC ./imgui/examples/libs/gl3w)
endif(WIN32)

target_link_libraries(sftlgui PUBLIC clip)
target_link_libraries(sftlgui PUBLIC nfd)

if (UNIX)
    target_link_libraries(sftlgui PUBLIC Vulkan::Vulkan)
    target_link_libraries(sftlgui PUBLIC glfw)
endif (UNIX)

