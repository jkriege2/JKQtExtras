cmake_minimum_required(VERSION 3.0)

# Project Name and Version
project(JKQtExtras LANGUAGES CXX VERSION 2020.01)


# set search path for CMake files
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Common Includes for JKQtExtras
include(jkqtextras_common_include)

# Project Name and Version
include(jkqtextras_lib_properties)

# CMake options with default values and description texts
include(jkqtextras_cmake_options)

# compiler settings for this lib
include(jkqtextras_common_compilersettings)

# include Qt with appropriate options to build this lib
include(jkqtextras_common_qtsettings)



# now add subdirectories with the library code ...
add_subdirectory(lib)
# ... and optionally the examples
if(JKQtExtras_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()



