cmake_minimum_required(VERSION 3.14)
project(metacar VERSION 0.4.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ── Dependencies ──────────────────────────────────────────────────────────────
include(FetchContent)
FetchContent_Declare(
    nlohmann_json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG        v3.12.0
)
FetchContent_MakeAvailable(nlohmann_json)

# ── Library target ────────────────────────────────────────────────────────────
add_library(metacar STATIC
    src/geometry.cpp
    src/models.cpp
    src/sockets.cpp
    src/scene_api.cpp
)

target_include_directories(metacar
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_link_libraries(metacar PUBLIC nlohmann_json::nlohmann_json)

# Ensure MSVC treats sources as UTF-8
if(MSVC)
    target_compile_options(metacar PRIVATE /utf-8)
endif()

# Platform-specific: link Winsock on Windows
if(WIN32)
    target_link_libraries(metacar PRIVATE ws2_32)
endif()

# ── Install rules ─────────────────────────────────────────────────────────────
include(GNUInstallDirs)

install(TARGETS metacar nlohmann_json
    EXPORT metacarTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY include/metacar
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT metacarTargets
    FILE metacarTargets.cmake
    NAMESPACE metacar::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/metacar
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/metacarConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/metacarConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/metacar
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/metacarConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/metacarConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/metacarConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/metacar
)
