cmake_minimum_required(VERSION 3.15 FATAL_ERROR)
project(libhuman VERSION 0.0.1 LANGUAGES CXX)

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

add_library(human
    src/Human.cpp
    src/Human.h
)

# Add an alias so that library can be used inside the build tree, e.g. when testing
add_library(Human::human ALIAS human)

# Set target properties
target_include_directories(human
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_compile_features(human PRIVATE cxx_auto_type)
target_compile_options(human PRIVATE
    $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>,$<CXX_COMPILER_ID:GNU>>:
    -Wall -Wextra -Wpedantic>
)

find_package(Utilities 1.0 REQUIRED)
target_link_libraries(human Utilities::Utilities)

# target_link_libraries(${CMAKE_PROJECT_NAME}
#     PUBLIC
#         Boost::headers RapidJSON::RapidJSON
#     PRIVATE
#         Boost::regex
# )

##############################################
# Installation instructions

include(GNUInstallDirs)
set(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/Human)

install(TARGETS human
    EXPORT human-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# This is required so that the exported target has the name Human and not human
set_target_properties(human PROPERTIES EXPORT_NAME Human)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

# Export the targets to a script
install(EXPORT human-targets
    FILE
        HumanTargets.cmake
    NAMESPACE
        Human::
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

# Create a ConfigVersion.cmake file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/HumanConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

configure_package_config_file(${CMAKE_CURRENT_LIST_DIR}/cmake/HumanConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/HumanConfig.cmake
    INSTALL_DESTINATION ${INSTALL_CONFIGDIR}
)

# Install the config, configversion and custom find modules
install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/HumanConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/HumanConfigVersion.cmake
    DESTINATION ${INSTALL_CONFIGDIR}
)

##############################################
## Exporting from the build tree
#configure_file(${CMAKE_CURRENT_LIST_DIR}/cmake/FindRapidJSON.cmake
#    ${CMAKE_CURRENT_BINARY_DIR}/FindRapidJSON.cmake
#    COPYONLY
# )

export(EXPORT human-targets
    FILE ${CMAKE_CURRENT_BINARY_DIR}/HumanTargets.cmake
    NAMESPACE Human::
)

# Register package in the User Package Registry
export(PACKAGE Human)

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