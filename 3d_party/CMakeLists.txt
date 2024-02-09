cmake_minimum_required(VERSION 3.15)

if (NOT TARGET nlohmann)
    add_library(nlohmann INTERFACE)
    add_library(nlohmann::json ALIAS nlohmann)
    target_include_directories(nlohmann INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/nlohmann)
endif()

if (NOT TARGET fmt) 
    add_subdirectory(fmt EXCLUDE_FROM_ALL)
endif()