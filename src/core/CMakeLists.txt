# TaticProject Core Engine Library

set(CORE_SOURCES
    Entity/Property.h
    Entity/PropertyContainer.h
    Entity/PropertyContainer.cpp
    Entity/Entity.h
    Entity/Entity.cpp
    Manager/EntityManager.h
    Manager/EntityManager.cpp
    Config/ConfigParser.h
    Config/ConfigParser.cpp
)

# Create Core library
add_library(TaticCore STATIC ${CORE_SOURCES})

# Include directories
target_include_directories(TaticCore PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Compile flags
if(MSVC)
    target_compile_options(TaticCore PRIVATE /W4)
else()
    target_compile_options(TaticCore PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Linking
target_link_libraries(TaticCore PUBLIC Qt6::Core)