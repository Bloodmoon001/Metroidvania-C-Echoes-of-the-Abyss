cmake_minimum_required(VERSION 3.20)
project(Metroidvania LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(MSVC)
    add_compile_options(/utf-8)
endif()
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
endif()
find_package(SFML COMPONENTS System Window Graphics CONFIG REQUIRED)
find_package(GTest CONFIG REQUIRED)
add_library(game_core
    src/core/Game.cpp
    src/entities/Player.cpp
    src/entities/Level.cpp
    src/entities/Enemy.cpp
    src/entities/Pickup.cpp
    src/entities/Collectible.cpp
)
target_include_directories(game_core PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(game_core PUBLIC SFML::Graphics SFML::Window SFML::System)
add_executable(app apps/main.cpp)
target_link_libraries(app PRIVATE game_core)
add_executable(tests tests/test_main.cpp)
target_link_libraries(tests PRIVATE game_core GTest::gtest_main)
set_target_properties(app tests PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

# Автокопирование ассетов при сборке
add_custom_command(TARGET app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:app>/assets"
)

