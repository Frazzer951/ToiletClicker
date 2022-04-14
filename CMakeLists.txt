cmake_minimum_required(VERSION 3.11.0)
project(Frazzer_Engine VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG master
)
FetchContent_GetProperties(sfml)
if (NOT sfml_POPULATED)
    set(BUILD_SHARED_LIBS OFF)
    FetchContent_Populate(sfml)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif ()

add_executable (${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} sfml-graphics)
