cmake_minimum_required(VERSION 4.0)
project(particle-sim LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ignore duplicated libraries warning
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-no_warn_duplicate_libraries")

find_package(SFML COMPONENTS Network Graphics Window Audio System CONFIG REQUIRED)

file(GLOB_RECURSE FILES_FOLDERS
    LIST_DIRECTORIES true
    ${CMAKE_SOURCE_DIR}/src/*
)

set(FILES "")
set(FOLDERS "")
foreach(item IN LISTS FILES_FOLDERS)
    string(REGEX MATCH "\\.cpp$" isCPPFile "${item}")
    string(REGEX MATCH "\\.hpp$" isHPPFile "${item}")
    if(IS_DIRECTORY "${item}")
        list(APPEND FOLDERS "${item}")
    elseif(isCPPFile)
        list(APPEND FILES "${item}")
    elseif(isHPPFile)
        list(APPEND FILES "${item}")
    endif()
endforeach()

message(STATUS "Files Detected:")
foreach(f IN LISTS FILES)
    message(STATUS "${f}")
endforeach()

message(STATUS "Folders Detected:")
foreach(dir IN LISTS FOLDERS)
    message(STATUS "${dir}")
endforeach()


add_executable(
    main
    ${FILES}
)

target_include_directories(
    main PRIVATE
    ${FOLDERS}
)

target_link_libraries(
    main PRIVATE
    SFML::Network
    SFML::Graphics
    SFML::Window
    SFML::Audio
    SFML::System
)
