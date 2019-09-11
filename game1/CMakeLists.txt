## Project Setup
cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME sprite-test)
set(APP_MAJOR_VERSION "1")
set(APP_MINOR_VERSION "1")
set(APP_PATCH_VERSION "0")
set(APP_VERSION_STRING "${APP_MAJOR_VERSION}.${APP_MINOR_VERSION}.${APP_PATCH_VERSION}")


# setup versioning based on the cmake version 
if (CMAKE_VERSION VERSION_LESS 3.0)
  PROJECT(${PROJECT_NAME} CXX)
  set(PROJECT_VERSION_MAJOR "${APP_MAJOR_VERSION}")
  set(PROJECT_VERSION_MINOR "${APP_MINOR_VERSION}")
  set(PROJECT_VERSION_PATCH"${APP_PATCH_VERSION}")
  set(PROJECT_VERSION "${APP_VERSION_STRING}")
else()
  cmake_policy(SET CMP0048 NEW)
  PROJECT(${PROJECT_NAME} VERSION "${APP_VERSION_STRING}" LANGUAGES CXX)
endif()

## Configurations

# Set the default path for built executables to the "bin" directory
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
# set the default path for built libraries to the "lib" directory
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# Uncomment the line below to set the build type
# set(CMAKE_BUILD_TYPE DEBUG)

# Extend the find_package search path

add_subdirectory(external/spdlog)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

## Configure the build system

# Add the include folder to the include path
include_directories(
  ${PROJECT_SOURCE_DIR}/include
  ${PROJECT_SOURCE_DIR}/persist/include
  ${PROJECT_SOURCE_DIR}/external/spdlog/include/spdlog
  
)

# Set the source files, headers, and link libraries
set(${PROJECT_NAME}_SRCS
            src/main.cpp 
            src/SimpleAnimationFrame.cpp 
            src/AnimatedSprite.cpp 
            src/ResourceManager.cpp 
            src/Sprite.cpp 
            src/BitmapResource.cpp
            src/Game.cpp
            src/MultiAnimatedSprite.cpp
            src/AnimationSet.cpp
            src/Spawner.cpp
            persist/src/AnimationSetFactory.cpp
            )

set(${PROJECT_NAME}_LINK_LIBS )

## Build the agame project

# Find Allegro

find_package(Allegro REQUIRED)

if(NOT TARGET spdlog)

    # Stand-alone build
    find_package(spdlog REQUIRED)
endif()


#find_package(allegro 5.0 REQUIRED COMPONENTS
#  main font ttf native_dialog primitives image
#)
include_directories(
    ${ALLEGRO_INCLUDE_DIRS}
 )

# Compile the Library
add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_SRCS})
# spdlog_enable_warnings(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} ${ALLEGRO_LIBRARIES} spdlog)


# Create logs directory
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/logs")
