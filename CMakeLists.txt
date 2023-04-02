cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project(ipsocket)

# Add client source files
set (CLIENT_SOURCES
    client/main.cpp
    client/player.cpp
) 
add_executable(client ${CLIENT_SOURCES})

# Add server source files
set (SERVER_SOURCES
    server/main.cpp
)
add_executable(server ${SERVER_SOURCES})

# Add SFML components to executables
find_package(TGUI 0.9 REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics window system network REQUIRED)
target_link_libraries(client sfml-graphics sfml-window sfml-system sfml-network tgui)
target_link_libraries(server sfml-graphics sfml-window sfml-system sfml-network tgui)

# Set output directory for executables
set_target_properties(client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set_target_properties(server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
