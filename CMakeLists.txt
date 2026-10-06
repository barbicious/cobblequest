cmake_minimum_required(VERSION 4.3)
project(cobblequest)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG master
)

FetchContent_MakeAvailable(glfw)

add_executable(cobblequest src/main.cpp vendor/glad/src/glad.c
        src/gfx/shader.cppm
        src/gfx/bindable.cppm
        src/gfx/buffer.cppm
        src/gfx/vertex_array.cppm
        src/gfx/vertex_buffer.cppm
)

file(GLOB_RECURSE glob_modules
    "src/**.cppm"
)

target_sources(cobblequest PRIVATE
        FILE_SET modules TYPE CXX_MODULES
        BASE_DIRS
        ${PROJECT_SOURCE_DIR}
        FILES
        ${glob_modules}
)

add_custom_target(copy_resources ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/res"
        "$<TARGET_FILE_DIR:cobblequest>/res"
        DEPENDS cobblequest
)



target_link_libraries(cobblequest PRIVATE glfw)

target_include_directories(cobblequest PRIVATE vendor/glad/include)