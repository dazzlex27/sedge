cmake_minimum_required(VERSION 3.10)
project(sedge)

file(GLOB_RECURSE SOURCES
                  "sedge/*.cpp"
                  "sedge/*.h"
                  "externals/glad/src/*.c"
)

find_package(glfw3 REQUIRED)
find_package(Freetype REQUIRED)

add_executable(sedge ${SOURCES})

target_include_directories(sedge PUBLIC
                            ${CMAKE_CURRENT_SOURCE_DIR}/sedge
                            ${CMAKE_CURRENT_SOURCE_DIR}/externals/glm
                            ${CMAKE_CURRENT_SOURCE_DIR}/externals/glfw-3.3.2/include
                            ${CMAKE_CURRENT_SOURCE_DIR}/externals/glad/include/glad
                            ${CMAKE_CURRENT_SOURCE_DIR}/externals/glad/include
                            ${CMAKE_CURRENT_SOURCE_DIR}/externals/STB
                            ${CMAKE_CURRENT_SOURCE_DIR}/externals/assimp/include
                            ${CMAKE_CURRENT_SOURCE_DIR}/externals/tinyobjloader
                            ${CMAKE_CURRENT_SOURCE_DIR}/externals/freetype-gl/include
                            ${FREETYPE_INCLUDE_DIRS}
)

link_directories(/opt/homebrew/lib)

set(FREETYPE_GL_LIB "${CMAKE_CURRENT_SOURCE_DIR}/externals/freetype-gl/lib/libfreetype-gl.a")

target_link_libraries(sedge PUBLIC
                            ${FREETYPE_LIBRARIES}
                            ${FREETYPE_GL_LIB}
                            glfw
)


if(APPLE)
    add_compile_options(-fsanitize=address -fno-omit-frame-pointer)
    add_link_options(-fsanitize=address)
endif()