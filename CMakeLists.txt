cmake_minimum_required(VERSION 3.16.0 FATAL_ERROR)

project(
        sample_app
        VERSION 0.0.1
        DESCRIPTION ""
        HOMEPAGE_URL  "https://github.com/AnahChacha/sample_app"
        LANGUAGES C
)

# Set warnings as errors
set(CMAKE_COMPILE_WARNING_AS_ERROR ON)

# Target Arch type
if(NOT CMAKE_VS_PLATFORM_NAME)
    set(CMAKE_VS_PLATFORM_NAME "Win32")
endif()
message("${CMAKE_VS_PLATFORM_NAME} architecture in use")

# Global configuration types
set(CMAKE_CONFIGURATION_TYPES
    "Debug"
    "Release"
    CACHE STRING "" FORCE
)

# Global compiler options
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_C_FLAGS "")
    set(CMAKE_C_FLAGS_DEBUG "")
    set(CMAKE_C_FLAGS_RELEASE "")
endif()

# Global linker options
if(MSVC)
    # remove default flags provided with CMake for MSVC
    set(CMAKE_EXE_LINKER_FLAGS "")
    set(CMAKE_MODULE_LINKER_FLAGS "")
    set(CMAKE_SHARED_LINKER_FLAGS "")
    set(CMAKE_STATIC_LINKER_FLAGS "")
    set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_DEBUG "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_DEBUG "${CMAKE_STATIC_LINKER_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_MODULE_LINKER_FLAGS_RELEASE "${CMAKE_MODULE_LINKER_FLAGS}")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS}")
    set(CMAKE_STATIC_LINKER_FLAGS_RELEASE "${CMAKE_STATIC_LINKER_FLAGS}")
endif()

# Common utils
include(CMake/Utils.cmake)

# Additional Global Settings(add specific info there)
include(CMake/GlobalSettingsInclude.cmake OPTIONAL)

# Use solution folders feature
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Sub-projects
add_subdirectory(sample_app)

# configure the solution template
include(CMake/Generators.cmake)
generate_sln_file(sample_app.sln.in  ${PROJECT_NAME})


