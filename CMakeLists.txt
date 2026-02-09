cmake_minimum_required(VERSION 3.21)
project(TaticProject VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")  # Visual Studio warnings

# Find packages
find_package(Qt6 COMPONENTS Core Gui Widgets REQUIRED)
find_package(Vulkan REQUIRED)

# Include subdirectories
add_subdirectory(src)
#add_subdirectory(tests EXCLUDE_FROM_ALL)

# Install targets
install(DIRECTORY config/ DESTINATION config)
install(DIRECTORY docs/ DESTINATION docs)