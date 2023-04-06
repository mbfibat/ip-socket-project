cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER "gcc")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pthread")
set(CMAKE_CXX_COMPILER "g++")

project(ipsocket)

# Add client source files
file(GLOB CLIENT_SOURCES "client/include/*.h" "client/src/*.cpp")
add_executable(client ${CLIENT_SOURCES})

# Add server source files
file(GLOB SERVER_SOURCES "server/include/*.h" "server/src/*.cpp")
add_executable(server ${SERVER_SOURCES})

# Add SFML components to executables
find_package(TGUI 0.9 REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics window system network audio REQUIRED)
target_link_libraries(client sfml-graphics sfml-window sfml-system sfml-network sfml-audio tgui)
target_link_libraries(server sfml-graphics sfml-window sfml-system sfml-network sfml-audio tgui)

# Set output directory for executables
set_target_properties(client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set_target_properties(server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
