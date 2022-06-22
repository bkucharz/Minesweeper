cmake_minimum_required(VERSION 3.15)
project(Saper)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(Saper main.cpp Cell.h Cell.cpp Globals.h Field.h Field.cpp)
target_link_libraries(Saper PRIVATE sfml-graphics)
target_compile_features(Saper PRIVATE cxx_std_17)

install(TARGETS Saper)