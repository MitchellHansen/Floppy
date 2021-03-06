# Check versions message(STATUS "CMake version: ${CMAKE_VERSION}") 
cmake_minimum_required(VERSION 3.1) 
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}) 

# Set the project name 
set(PNAME floppy-bird) 
project(${PNAME}) 

# Set up variables, and find SFML 
set(SFML_ROOT root CACHE STRING "User specified path") 
set(SFML_COMPONENTS graphics window system network audio) 
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(SFML 2.1 COMPONENTS ${SFML_COMPONENTS} REQUIRED)
message(STATUS "SFML found: ${SFML_FOUND}") 

# Include the directories for the main program, GL, CL and SFML's headers 
include_directories(${SFML_INCLUDE_DIR}) 
include_directories(include) 

# Set the sources, allows VS to filter them properly 
file(GLOB SOURCES "*.cpp") 
file(GLOB HEADERS "*.h")

add_executable(${PNAME} ${SOURCES}) 

# Link CL, GL, and SFML 
target_link_libraries (${PNAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES}) 

# Setup to use C++11 + others
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") 
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread") 
set_property(TARGET ${PNAME} PROPERTY CXX_STANDARD 11) # Use C++11