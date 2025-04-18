# SDL CMake configuration file:
# This file is meant to be placed in lib/cmake/SDL3_ttf subfolder of a reconstructed Android SDL3_ttf SDK

cmake_minimum_required(VERSION 3.0...3.28)

include(FeatureSummary)
set_package_properties(SDL3_ttf PROPERTIES
    URL "https://www.libsdl.org/projects/SDL_ttf/"
    DESCRIPTION "Support for TrueType (.ttf) font files with Simple Directmedia Layer"
)

# Copied from `configure_package_config_file`
macro(set_and_check _var _file)
    set(${_var} "${_file}")
    if(NOT EXISTS "${_file}")
        message(FATAL_ERROR "File or directory ${_file} referenced by variable ${_var} does not exist !")
    endif()
endmacro()

# Copied from `configure_package_config_file`
macro(check_required_components _NAME)
    foreach(comp ${${_NAME}_FIND_COMPONENTS})
        if(NOT ${_NAME}_${comp}_FOUND)
            if(${_NAME}_FIND_REQUIRED_${comp})
                set(${_NAME}_FOUND FALSE)
            endif()
        endif()
    endforeach()
endmacro()

set(SDL3_ttf_FOUND TRUE)

set(SDLTTF_VENDORED TRUE)

set(SDLTTF_HARFBUZZ TRUE)
set(SDLTTF_FREETYPE TRUE)

if(SDL_CPU_X86)
    set(_sdl_arch_subdir "x86")
elseif(SDL_CPU_X64)
    set(_sdl_arch_subdir "x86_64")
elseif(SDL_CPU_ARM32)
    set(_sdl_arch_subdir "armeabi-v7a")
elseif(SDL_CPU_ARM64)
    set(_sdl_arch_subdir "arm64-v8a")
else()
    set(SDL3_ttf_FOUND FALSE)
    return()
endif()

get_filename_component(_sdl3ttf_prefix "${CMAKE_CURRENT_LIST_DIR}/.." ABSOLUTE)
get_filename_component(_sdl3ttf_prefix "${_sdl3ttf_prefix}/.." ABSOLUTE)
get_filename_component(_sdl3ttf_prefix "${_sdl3ttf_prefix}/.." ABSOLUTE)
set_and_check(_sdl3ttf_prefix          "${_sdl3ttf_prefix}")
set_and_check(_sdl3ttf_include_dirs    "${_sdl3ttf_prefix}/include")

set_and_check(_sdl3ttf_lib             "${_sdl3ttf_prefix}/lib/${_sdl_arch_subdir}/libSDL3_ttf.so")

unset(_sdl_arch_subdir)
unset(_sdl3ttf_prefix)

# All targets are created, even when some might not be requested though COMPONENTS.
# This is done for compatibility with CMake generated SDL3_ttf-target.cmake files.

if(EXISTS "${_sdl3ttf_lib}")
    if(NOT TARGET SDL3_ttf::SDL3_ttf-shared)
        add_library(SDL3_ttf::SDL3_ttf-shared SHARED IMPORTED)
        set_target_properties(SDL3_ttf::SDL3_ttf-shared
            PROPERTIES
                IMPORTED_LOCATION "${_sdl3ttf_lib}"
                INTERFACE_INCLUDE_DIRECTORIES "${_sdl3ttf_include_dirs}"
                COMPATIBLE_INTERFACE_BOOL "SDL3_SHARED"
                INTERFACE_sdl3ttf_SHARED "ON"
                COMPATIBLE_INTERFACE_STRING "SDL_VERSION"
                INTERFACE_SDL_VERSION "SDL3"
    )
    endif()
    set(SDL3_ttf_sdl3ttf_ttf-shared_FOUND TRUE)
else()
    set(SDL3_ttf_sdl3ttf_ttf-shared_FOUND FALSE)
endif()
unset(_sdl3ttf_lib)
unset(_sdl3ttf_include_dirs)

set(SDL3_ttf_SDL3_ttf-static_FOUND FALSE)

if(SDL3_ttf_SDL3_ttf-shared_FOUND OR SDL3_ttf_SDL3_ttf-static_FOUND)
    set(SDL3_ttf_SDL3_ttf_FOUND TRUE)
endif()

function(_sdl_create_target_alias_compat NEW_TARGET TARGET)
    if(CMAKE_VERSION VERSION_LESS "3.18")
        # Aliasing local targets is not supported on CMake < 3.18, so make it global.
        add_library(${NEW_TARGET} INTERFACE IMPORTED)
        set_target_properties(${NEW_TARGET} PROPERTIES INTERFACE_LINK_LIBRARIES "${TARGET}")
    else()
        add_library(${NEW_TARGET} ALIAS ${TARGET})
    endif()
endfunction()

# Make sure SDL3_ttf::SDL3_ttf always exists
if(NOT TARGET SDL3_ttf::SDL3_ttf)
    if(TARGET SDL3_ttf::SDL3_ttf-shared)
        _sdl_create_target_alias_compat(SDL3_ttf::SDL3_ttf SDL3_ttf::SDL3_ttf-shared)
    endif()
endif()

check_required_components(SDL3_ttf)
