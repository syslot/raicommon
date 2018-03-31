cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(GNUInstallDirs)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
project(raiCommon)

##############################
############ Path ############
##############################
set(CMAKE_PACKAGE_INSTALL_DIR
        "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/cmake"
        CACHE PATH "The directory relative to CMAKE_PREFIX_PATH where raiCommonConfig.cmake is installed")

set(RAI_GRAPHICS_OPENGL_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(CONFIG_FILE_NAME ${PROJECT_NAME}Config.cmake)
set(TARGETS_EXPORT_NAME ${PROJECT_NAME}Targets)
set(TARGETS_LIB_NAME ${PROJECT_NAME}Lib)

##############################
############ pkgs ############
##############################
find_package( Eigen3 REQUIRED )
include_directories( ${EIGEN3_INCLUDE_DIR} )
link_directories(/usr/lib)

find_package( Boost COMPONENTS system filesystem REQUIRED )
include_directories( ${Boost_INCLUDE_DIR} )
link_directories(${Boost_LIBRARY_DIRS})

##############################
########### Utils ############
##############################
add_library(rai_graph STATIC src/utils/rai_graph/gnuplotter.cpp)
add_library(rai_timer STATIC src/utils/rai_timer/RAI_timer.cpp)
add_library(rai_logger STATIC src/utils/rai_logger/RAI_logger.cpp)

set(rai_common rai_graph rai_timer rai_logger)
set(rai_common_link ${rai_common} ${Boost_LIBRARIES})
set(RAICOMMON_LIB_DIR ${CMAKE_BINARY_DIR}/lib CACHE PATH "rai lib directory")

# --------------------------------------------------------------------
# package raiCommon
export(PACKAGE ${PROJECT_NAME})

# build tree
set(CONF_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include" ${Boost_INCLUDE_DIR})

# create raiGraphicsOpenglConfig.cmake.in
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/${CONFIG_FILE_NAME}.in
        ${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_FILE_NAME} @ONLY)

# install package
install(TARGETS                 ${rai_common}
        EXPORT                  ${TARGETS_EXPORT_NAME}
        LIBRARY DESTINATION     lib
        ARCHIVE DESTINATION     lib
        )

# install raiCommonConfig.cmake file to config cmake path
install(FILES           ${CMAKE_CURRENT_BINARY_DIR}/${CONFIG_FILE_NAME}
        DESTINATION     ${CMAKE_PACKAGE_INSTALL_DIR})

# --------------------------------------------------------------------
# test
add_executable(loggerTest test/loggerTest.cpp)
target_link_libraries(loggerTest ${rai_common_link})