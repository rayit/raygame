cmake_minimum_required(VERSION 3.15)

project(raygame)

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

# Fetch raylib
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG master # Or specify a specific version/tag
)
FetchContent_MakeAvailable(raylib)

# Include directories
include_directories(${raylib_SOURCE_DIR}/src include)

# Include directories
include_directories(include)

# Source files
file(GLOB SOURCES "src/*.c")

# Executable
add_executable(raygame ${SOURCES})

# Link libraries
target_link_libraries(raygame raylib m)