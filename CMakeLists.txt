
cmake_minimum_required(VERSION 3.10)

project(meshLib VERSION 1.0.0 LANGUAGES CXX)

# lib

add_library(meshLib STATIC
    meshLib/apt.cpp
    meshLib/base.cpp
    meshLib/box.cpp
    meshLib/cach.cpp
    meshLib/cclt.cpp
    meshLib/ckat.cpp
    meshLib/cldf.cpp
    meshLib/cmp.cpp
    meshLib/cshd.cpp
    meshLib/cstb.cpp
    meshLib/dtii.cpp
    meshLib/eft.cpp
    meshLib/flor.cpp
    meshLib/foot.cpp
    meshLib/ilf.cpp
    meshLib/lod.cpp
    meshLib/mlod.cpp
    meshLib/model.cpp
    meshLib/msh.cpp
    meshLib/mshVertex.cpp
    meshLib/mshVertexData.cpp
    meshLib/mshVertexIndex.cpp
    meshLib/peft.cpp
    meshLib/prto.cpp
    meshLib/sbot.cpp
    meshLib/scot.cpp
    meshLib/sd2d.cpp
    meshLib/sd3d.cpp
    meshLib/shot.cpp
    meshLib/sht.cpp
    meshLib/skmg.cpp
    meshLib/sktm.cpp
    meshLib/slod.cpp
    meshLib/smat.cpp
    meshLib/spam.cpp
    meshLib/stat.cpp
    meshLib/ster.cpp
    meshLib/stot.cpp
    meshLib/str.cpp
    meshLib/swts.cpp
    meshLib/trn.cpp
    meshLib/trnAffector.cpp
    meshLib/trnBoundary.cpp
    meshLib/trnLayer.cpp
    meshLib/ws.cpp)

add_library(meshLib::meshLib ALIAS meshLib)

if(WIN32)
    target_compile_options(meshLib PRIVATE "-wd4267")
endif()

target_include_directories(meshLib
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# executables

add_executable(readLOD tools/readLOD/readLOD.cpp)
target_link_libraries(readLOD meshLib)

if(WIN32)
    target_compile_options(readLOD PRIVATE "-wd4267")
endif()

add_executable(readSWG tools/readSWG/readSWG.cpp)
target_link_libraries(readSWG meshLib)

if(WIN32)
    target_compile_options(readSWG PRIVATE "-wd4267")
endif()

# installation

include(GNUInstallDirs)

install(
    TARGETS
        readLOD
        readSWG
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/meshLib)

install(
    TARGETS
        meshLib
    EXPORT
        meshLibTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(EXPORT meshLibTargets
    FILE meshLibTargets.cmake
    NAMESPACE meshLib::
    DESTINATION ${INSTALL_CONFIGDIR}
)

install(DIRECTORY meshLib/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/meshLib
    FILES_MATCHING PATTERN "*.h*"
)

# ConfigVersion file

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/meshLibConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/meshLibConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/meshLibConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

install(
    FILES
      ${CMAKE_CURRENT_BINARY_DIR}/meshLibConfig.cmake
      ${CMAKE_CURRENT_BINARY_DIR}/meshLibConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)
