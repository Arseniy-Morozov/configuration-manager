cmake_minimum_required(VERSION 3.25)
project(configuration_manager)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")

find_package(sdbus-c++ REQUIRED)

add_executable(configManager
    src/main.cpp
    src/ConfigurationManager.cpp
    src/ApplicationObject.cpp
)

target_link_libraries(configManager PRIVATE sdbus-c++)
