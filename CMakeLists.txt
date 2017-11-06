cmake_minimum_required(VERSION 3.5)
project(raicommon)
set(CMAKE_CXX_STANDARD 14)

include(GNUInstallDirs)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

##############################
############ Path ############
##############################
set(CMAKEPACKAGE_INSTALL_DIR
        "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_DATADIR}/${PROJECT_NAME}/cmake"
        CACHE PATH "The directory relative to CMAKE_PREFIX_PATH where RAIConfig.cmake is installed"
        )

##############################
############ pkgs ############
##############################
find_package( Eigen3 REQUIRED )
include_directories( ${EIGEN3_INCLUDE_DIR} )
link_directories(/usr/lib)

##############################
########### Utils ############
##############################
add_library(rai_graph src/utils/rai_graph/gnuplotter.cpp)
install(TARGETS rai_graph EXPORT RAICOMMONTargets DESTINATION ${CMAKE_BINARY_DIR}/lib)
add_library(rai_timer src/utils/rai_timer/RAI_timer.cpp)
install(TARGETS rai_timer EXPORT RAICOMMONTargets DESTINATION ${CMAKE_BINARY_DIR}/lib)
add_library(rai_logger src/utils/rai_logger/RAI_logger.cpp)
install(TARGETS rai_logger EXPORT RAICOMMONTargets DESTINATION ${CMAKE_BINARY_DIR}/lib)
set(rai_common ${rai_common} rai_graph rai_timer rai_logger)

# --------------------------------------------------------------------
# package raiGraphics
export(PACKAGE ${PROJECT_NAME})

# build tree
set(CONF_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

# create raiGraphicsOpenglConfig.cmake.in
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/raicommonConfig.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/raicommonConfig.cmake @ONLY)

# install package
install(TARGETS                 ${TARGETS}
        EXPORT                  RAICOMMONTargets
        LIBRARY DESTINATION     lib
        ARCHIVE DESTINATION     lib
        #        INCLUDES DESTINATION    include
        )

# install raiGraphicsConfig.cmake file to config cmake path
install(FILES           ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake
        DESTINATION     ${CMAKEPACKAGE_INSTALL_DIR})