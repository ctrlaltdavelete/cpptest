get_filename_component(UTILITIES_CMAKE_DIR "${CMAKE_CURRENT_LIST_FILE}" PATH)
include(CMakeFindDependencyMacro)

list(APPEND CMAKE_MODULE_PATH ${UTILITIES_CMAKE_DIR})
# NOTE: to find FindRapidJSON.cmake
#find_dependency(RapidJSON )
#list(REMOVE_AT CMAKE_MODULE_PATH -1)

#find_dependency(boost_regex )

if(NOT TARGET Utilities::Utilities)
    include("${UTILITIES_CMAKE_DIR}/UtilitiesTargets.cmake")
endif()

set(UTILITIES_LIBRARIES Utilities::Utilities)
