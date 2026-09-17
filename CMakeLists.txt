cmake_minimum_required(VERSION 3.28.0)
project(ynopdesktop VERSION 0.1.1 LANGUAGES C CXX)
include(cmake/CPM.cmake)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_CONFIGURATION_TYPES)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(saucer_backend "Qt" CACHE STRING "Saucer backend" FORCE)
endif()

file(GLOB_RECURSE SOURCE_FILES 
    "src/*.cpp"
    "src/*.cxx"
    "src/*.cc"
)

CPMAddPackage(
  NAME           saucer
  VERSION        8.2.0
  GIT_REPOSITORY "https://github.com/saucer/saucer"
  GIT_TAG        "ver/8.2.0"
)


add_executable(ynopdesktop ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE saucer::saucer)


