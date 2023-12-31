cmake_minimum_required(VERSION 3.5)
project(Viewer)

include(FetchContent)

set(CMAKE_CXX_STANDARD 11)

# Set the build type to Debug
set(CMAKE_BUILD_TYPE Debug)

find_package(OpenGL REQUIRED)

# SDL2
FetchContent_Declare(
    SDL2 
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.28.3)
FetchContent_MakeAvailable(SDL2)

# SDL2 Image
FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG SDL2
    )
FetchContent_MakeAvailable(SDL2_image)

# GLM 
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.9.8)
    FetchContent_MakeAvailable(glm)

# IMGUI
FetchContent_Declare(
    imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.89.9)
FetchContent_MakeAvailable(imgui)

# GLAD
add_subdirectory(vendored/glad EXCLUDE_FROM_ALL)

file(GLOB SRC_FILES 
    shaders/*.glsl
    headers/*.hpp src/*.cpp 
    headers/**/*.hpp src/**/*.cpp 

    # imgui targets
    ${CMAKE_BINARY_DIR}/_deps/imgui-src/backends/imgui_impl_sdl2.cpp 
    ${CMAKE_BINARY_DIR}/_deps/imgui-src/backends/imgui_impl_opengl3.cpp
    ${CMAKE_BINARY_DIR}/_deps/imgui-src/imgui*.cpp
)

# sources
add_executable(Viewer WIN32 main.cpp ${SRC_FILES})

# SDL2::SDL2main may or may not be available. It is e.g. required by Windows GUI applications
if(TARGET SDL2::SDL2main)
    # It has an implicit dependency on SDL2 functions, so it MUST be added before SDL2::SDL2 (or SDL2::SDL2-static)
    target_link_libraries(Viewer PRIVATE SDL2::SDL2main)
endif()

# link libraries
target_link_libraries(Viewer PRIVATE SDL2::SDL2 SDL2_image Glad glm)

include_directories(${CMAKE_BINARY_DIR}/_deps/sdl2_image-src/include)
include_directories(${CMAKE_BINARY_DIR}/_deps/imgui-src) # add imgui to include path
include_directories("headers")
include_directories("vendored")


if(WIN32)
    # copy SDL2.dll, SDL2_image.dll to the output directory
    add_custom_command(TARGET Viewer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SDL2::SDL2> $<TARGET_FILE_DIR:Viewer>
            $<TARGET_FILE:SDL2_image::SDL2_image> $<TARGET_FILE_DIR:Viewer>
            )
endif()

file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/)
file(COPY ${CMAKE_SOURCE_DIR}/shaders DESTINATION ${CMAKE_BINARY_DIR}/Debug)
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR}/Debug)