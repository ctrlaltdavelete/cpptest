cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(libutils VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# Make sure that custom modules like cmake/FindRapidJSON.cmake are found
#list(INSERT CMAKE_MODULE_PATH 0 ${CMAKE_SOURCE_DIR}/cmake)

##############################################
# Find system dependencies
#set(MIN_BOOST_VERSION 1.65)
#find_package(Boost ${MIN_BOOST_VERSION} REQUIRED COMPONENTS regex)

#set(MIN_RapidJSON_VERSION 1.1)
#find_package(RapidJSON ${MIN_RapidJSON_VERSION} REQUIRED)

##############################################
# Create target and set properties

add_library(utils
    src/NumberUtils.cpp
)

# Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(Utilities::utils ALIAS utils)

# Set target properties
target_include_directories(utils
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(utils PRIVATE cxx_auto_type)
target_compile_options(utils PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
    -Wall -Wextra -Wpedantic>
)

# target_link_libraries(${CMAKE_PROJECT_NAME}
#     PUBLIC
#         Boost::headers RapidJSON::RapidJSON
#     PRIVATE
#         Boost::regex
# )

##############################################
# Installation instructions

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/Utilities)

install(TARGETS utils
    EXPORT utils-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# This is required so that the exported target has the name Utilities and not utils
set_target_properties(utils PROPERTIES EXPORT_NAME Utilities)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export the targets to a script
install(EXPORT utils-targets
    FILE
        UtilitiesTargets.cmake
    NAMESPACE
        Utilities::
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

# Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/UtilitiesConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/UtilitiesConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/UtilitiesConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

# Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/UtilitiesConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/UtilitiesConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################
## Exporting from the build tree
#configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/FindRapidJSON.cmake
#    ${CMAKE_CURRENT_BINARY_DIR}/FindRapidJSON.cmake
#    COPYONLY
# )

export(EXPORT utils-targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/UtilitiesTargets.cmake
    NAMESPACE Utilities::
)

# Register package in the User Package Registry
export(PACKAGE Utilities)

##############################################
## Add tests
enable_testing()
add_subdirectory(test)

# ##############################################
# ## Add GCOVR
# # now for coverage bits
# set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
# if (CMAKE_COMPILER_IS_GNUCXX)
#     include(CodeCoverage)
#     append_coverage_compiler_flags()

#     # we need to turn off optimization for non-skewed coverage reports
#     set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -O0")
#     set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")

#     # optional excludes - None needed here
#     #    set(COVERAGE_EXCLUDES)

#     # importantly, set the path to the gcovr executable that you downladed
#     set(GCOVR_PATH "/usr/bin/gcovr")
#     # Works
#     setup_target_for_coverage_gcovr_xml(
#             NAME TestDoMathCoverageXml
#             EXECUTABLE TestDoMath
#             DEPENDENCIES TestDoMath DoMath
#     )
#     # Works
#     setup_target_for_coverage_gcovr_html(
#             NAME TestDoMathCoverageHtml
#             EXECUTABLE TestDoMath
#             DEPENDENCIES TestDoMath DoMath
#     )
#     # This one did not work for me:
#     setup_target_for_coverage_lcov(
#             NAME TestDoMathCoverageLcov
#             EXECUTABLE TestDoMath
#             DEPENDENCIES TestDoMath DoMath
#     )
# endif ()