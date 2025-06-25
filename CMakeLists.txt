cmake_minimum_required(VERSION 3.15...3.30)

project(
    TowerDefense 
    VERSION 0.1
    DESCRIPTION "Tower defense game using Lua and Irrlicht engine"
    LANGUAGES CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(CMAKE_CXX_EXTENSIONS OFF)

    set_property(GLOBAL PROPERTY USE_FOLDERS ON)

    include(CTest)

    # Add doc generation here?
endif()

find_package(irrlicht CONFIG REQUIRED)
find_package(Lua REQUIRED)
find_package(Catch REQUIRED)
add_subdirectory(src)

add_subdirectory(apps)

#if(BUILD_TESTING)
#    add_subdirectory(tests)
#endif()
