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

#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2main")
#    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lSDL2")

    # sudo apt install libglew-dev
    # libglfw3-dev

#    find_package(glfw3 REQUIRED)
#    find_package(GLEW REQUIRED)
    find_package(OpenGL REQUIRED)
    find_package(SDL2 REQUIRED)

    # Use vulkan headers from glfw:
#    include_directories(${GLFW_DIR}/deps)
#    include_directories(${GLEW_INCLUDE_DIRS})
    include_directories(${SDL2_INCLUDE_DIRS})
    link_directories(${SDL2_INCLUDE_DIRS})
    include_directories(${OPENGL_INCLUDE_DIRS})
    link_directories(${OPENGL_LIBRARY_DIRS})

    include_directories(./lib/imgui/backends/)
    include_directories(./lib/imgui/examples/libs/)

    file(GLOB src_imgui
            ./lib/imgui/*.cpp
            ./lib/imgui/backends/imgui_impl_opengl3.cpp
            ./lib/imgui/backends/imgui_impl_sdl.cpp
            )

endif (UNIX)

if (WIN32)

    file(GLOB src_imgui
            ./lib/imgui/*.cpp
            ./lib/imgui/backends/imgui_impl_opengl3.cpp
            ./lib/imgui/backends/imgui_impl_glfw.cpp
            ./lib/imgui/examples/libs/gl3w/GL/gl3w.c
            )

endif (WIN32)

file(GLOB src_implot
        ./lib/implot/*.cpp
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
    target_link_libraries(lib_gui PUBLIC gdi32)
    target_link_libraries(lib_gui PUBLIC shell32)
    target_link_libraries(lib_gui PUBLIC glu32)

    find_library(lib_glfw3 glfw3 HINTS lib/imgui/examples/libs/glfw/lib-vc2010-64)
    target_link_libraries(lib_gui PUBLIC ${lib_glfw3})

    target_include_directories(lib_gui PUBLIC ./lib/imgui/backends/)
    target_include_directories(lib_gui PUBLIC ./lib/imgui/examples/libs/glfw/include)
    target_include_directories(lib_gui PUBLIC ./lib/imgui/examples/libs/gl3w)
endif(WIN32)

target_link_libraries(lib_gui PUBLIC clip)
target_link_libraries(lib_gui PUBLIC nfd)

if (UNIX)

#target_link_libraries(lib_gui PUBLIC glfw)
#target_link_libraries(lib_gui PUBLIC ${GLEW_LIBRARIES})
target_link_libraries(lib_gui PUBLIC ${SDL2_LIBRARIES})
target_link_libraries(lib_gui PUBLIC OpenGL::GL)
target_link_libraries(lib_gui PUBLIC ${CMAKE_DL_LIBS})
target_link_libraries(lib_gui PUBLIC ${OPENGL_LIBRARIES})

endif (UNIX)


