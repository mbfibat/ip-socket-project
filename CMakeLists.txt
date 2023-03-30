cmake_minimum_required(VERSION 3.0)

project(ipsocket)

# Add client source files
set(CLIENT_SOURCES
    client/main.cpp
) 
add_executable(client ${CLIENT_SOURCES})

# Set output directory for executables
set (EXECUTABLES
    client
)
set_target_properties(${EXECUTABLES} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
