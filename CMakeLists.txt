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
project(raiCommon)

# Include CMake helper packages and utilities
include(GNUInstallDirs)

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

# Set GCC version
set(CMAKE_CXX_COMPILER "/usr/bin/g++-6")

# Enable the POSITION_INDEPENDENT_CODE property for all targets
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

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
if (DEFINED USE_EXPORTED_LIBS)
  list(APPEND ${PROJECT_NAME}_INCLUDE_DIRS "${CMAKE_INSTALL_PREFIX}/include")
else()
  list(APPEND ${PROJECT_NAME}_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")
endif ()
set(CONFIG_INCLUDE_DIRS "${${PROJECT_NAME}_INCLUDE_DIRS}")
set(CONFIG_LIBRARIES_DIRS "${CMAKE_INSTALL_PREFIX}/lib/")
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
