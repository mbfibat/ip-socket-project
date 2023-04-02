cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")

project(ipsocket)

# Add client source files
set (CLIENT_SOURCES
    client/main.cpp
) 
add_executable(client ${CLIENT_SOURCES})

# Add server source files
set (SERVER_SOURCES
    server/main.cpp
)
add_executable(server ${SERVER_SOURCES})

# Add SFML components to executables
find_package(SFML 2.5 COMPONENTS graphics window system network REQUIRED)
# target_link_libraries(client sfml-graphics sfml-window sfml-system sfml-network)
target_link_libraries(server sfml-graphics sfml-window sfml-system sfml-network)

# Set output directory for executables
set_target_properties(client PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)
set_target_properties(server PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# Find TGUI
find_package(TGUI REQUIRED)

# Include TGUI headers
# include_directories(${TGUI_INCLUDE_DIR})

# Link to TGUI libraries
# target_link_libraries(client PRIVATE tgui)
target_link_libraries(client sfml-graphics sfml-window sfml-system sfml-network tgui)


