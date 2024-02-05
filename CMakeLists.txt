cmake_minimum_required(VERSION 3.5)

project(guacamole_client LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



find_package(Qt5 COMPONENTS Widgets WebSockets Network REQUIRED)
file(GLOB SOURCES "*.h" "*.cpp" "*.ui")
add_executable(guacamole_client ${SOURCES}
)

target_link_libraries(guacamole_client PRIVATE Qt5::Widgets Qt5::WebSockets Qt5::Network)
