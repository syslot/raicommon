#=============================================================================
# Copyright (C) 2018, Jemin Hwangbo
# All rights reserved.
# https://bitbucket.org/leggedrobotics/rai_common
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================

cmake_minimum_required(VERSION 3.5)
project(raicommon)

# Include CMake helper packages and utilities
include(GNUInstallDirs)

#==
# Options
#==

option(USE_EXPORTED_LIBS "Configures the CMake package for installation in a multi-package workspace such as Catkin." OFF)

#==
# Dependencies
#==

# Find Eigen3 only if not already specified
if(NOT DEFINED EIGEN3_INCLUDE_DIR)
  find_package(Eigen3 REQUIRED)
  message(STATUS "${PROJECT_NAME}: Found Eigen3: ${EIGEN3_INCLUDE_DIR}")
else()
  message(STATUS "${PROJECT_NAME}: User specified Eigen3: ${EIGEN3_INCLUDE_DIR}")
endif()
list(APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${EIGEN3_INCLUDE_DIR})

# Boost dependencies
find_package(Boost COMPONENTS thread system filesystem REQUIRED)
if (Boost_FOUND)
  message(STATUS "${PROJECT_NAME}: Found Boost!")
  list(APPEND ${PROJECT_NAME}_INCLUDE_DIRS ${Boost_INCLUDE_DIR})
  list(APPEND ${PROJECT_NAME}_LIBRARIES ${Boost_LIBRARIES})
endif()

#==
# Build configuration
#==

# Set C++ language version
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable the POSITION_INDEPENDENT_CODE property for all targets
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Set GCC flags
add_compile_options("-pthread")
add_compile_options("-Wl,--no-as-needed")
add_compile_options("-mtune=native")
add_compile_options("-Wall" "-Wextra")

# Set a default build if no build type is set
if(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE RelWithDebInfo)
endif(NOT CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
message(STATUS "${PROJECT_NAME}: CMAKE_BUILD_TYPE is set to:  ${CMAKE_BUILD_TYPE}")

# Set optimization flags depending on set build-type
if(CMAKE_BUILD_TYPE MATCHES Debug)
  add_compile_options("-O0" "-g")
  add_definitions(-DRAIDEBUG)
elseif(CMAKE_BUILD_TYPE MATCHES RelWithDebInfo)
  add_compile_options("-g" "-w" "-O2")
  add_definitions(-DRAIDEBUG)
elseif(CMAKE_BUILD_TYPE MATCHES Release)
  add_compile_options("-w" "-O3")
  remove_definitions(-DRAIDEBUG)
else()
  message(FATAL_ERROR "${PROJECT_NAME}: Invalid or unsupported build-type '${CMAKE_BUILD_TYPE}'")
endif()

# Set include directories
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${${PROJECT_NAME}_INCLUDE_DIRS}
)

# Set search paths for link libraries
link_directories(
  /usr/lib
)

# Set the link targets
link_libraries(
  ${${PROJECT_NAME}_LIBRARIES}
)

#==
# Build targets
#==

# Add the gnuplot-based plotting and visualization library
add_library(rai_common_graph STATIC src/utils/rai_graph/gnuplotter.cpp)
list(APPEND ${PROJECT_NAME}_TARGETS rai_common_graph)

# Add the smart-timer library
add_library(rai_common_timer STATIC src/utils/rai_timer/RAI_timer.cpp)
list(APPEND ${PROJECT_NAME}_TARGETS rai_common_timer)

# Add the logging utilities library
add_library(rai_common_logger STATIC src/utils/rai_logger/RAI_logger.cpp)
list(APPEND ${PROJECT_NAME}_TARGETS rai_common_logger)

# Tests
add_executable(test_Logger test/test_logger.cpp)
target_link_libraries(test_Logger ${${PROJECT_NAME}_TARGETS})
add_executable(examples_plotting src/examples/plotting_examples.cpp)
target_link_libraries(examples_plotting ${${PROJECT_NAME}_TARGETS})

#==
# Package configuration: for use via find_package()
#==

# Set the install destination for the package configuration
set(CMAKE_PACKAGE_CONFIG_INSTALL_DIR
  "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/cmake"
  CACHE PATH "The directory relative to CMAKE_PREFIX_PATH where ${PROJECT_NAME}Config.cmake is installed")

# Set name of the package configuration file
set(CONFIG_FILE_NAME ${PROJECT_NAME}Config.cmake)

# Set the configuration variables
if (USE_EXPORTED_LIBS)
  list(APPEND ${PROJECT_NAME}_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/include")
else()
  list(APPEND ${PROJECT_NAME}_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")
endif ()
set(CONFIG_INCLUDE_DIRS "${${PROJECT_NAME}_INCLUDE_DIRS}")
set(CONFIG_LIBRARIES_DIRS "${CMAKE_INSTALL_PREFIX}/lib/")
set(CONFIG_LIBRARIES "${${PROJECT_NAME}_LIBRARIES}")
set(CONFIG_EXPORTED_TARGETS "${${PROJECT_NAME}_TARGETS}")

# Generate the package configuration file
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/${CONFIG_FILE_NAME}.in
  ${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_FILE_NAME} @ONLY)

#==
# Package installation
#==

# Install the package configuration file
install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_FILE_NAME}
  DESTINATION ${CMAKE_PACKAGE_CONFIG_INSTALL_DIR}
)

# Install C++ library headers
install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include
  DESTINATION ${CMAKE_INSTALL_PREFIX}
)

# Install C++ libraries
install(
  TARGETS ${${PROJECT_NAME}_TARGETS}
  LIBRARY DESTINATION lib/
  ARCHIVE DESTINATION lib/
)

# EOF
