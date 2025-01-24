cmake_minimum_required(VERSION 3.30)

project(TowerDefense LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_FILES
    src/main.cpp
    src/Game.cpp
    src/Gameobject.cpp
    src/MyEventReceiver.cpp
    src/WideText.cpp
)

set(HEADER_FILES 
    src/Game.h
    src/Gameobject.h
    src/MyEventReceiver.h
    src/WideText.h
)

add_executable(TowerDefense ${SOURCE_FILES} ${HEADER_FILES})

target_include_directories(TowerDefense PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_include_directories(TowerDefense PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/lua/include)
target_link_directories(TowerDefense PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/lua)
target_link_libraries(TowerDefense PUBLIC lua54)

target_include_directories(TowerDefense PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/irrlicht-1.8.5/include)
target_link_directories(TowerDefense PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/libs/irrlicht-1.8.5/lib/Win64-visualStudio)
target_link_libraries(TowerDefense PUBLIC Irrlicht)

# Adds dlls for lua and irrlicht where the exe is located for both debug and release
add_custom_command(TARGET TowerDefense POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/libs/lua/lua54.dll"      # <--this is in-file
        $<TARGET_FILE_DIR:TowerDefense>)                 # <--this is out-file path

add_custom_command(TARGET TowerDefense POST_BUILD        # Adds a post-build event to MyTest
    COMMAND ${CMAKE_COMMAND} -E copy_if_different  # which executes "cmake - E copy_if_different..."
        "${PROJECT_SOURCE_DIR}/libs/irrlicht-1.8.5/bin/Win64-VisualStudio/Irrlicht.dll"      # <--this is in-file
        $<TARGET_FILE_DIR:TowerDefense>)                 # <--this is out-file path

# Copy the assets to the build directory
add_custom_target(copy_assets
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy-assets.cmake
)
add_dependencies(TowerDefense copy_assets)

#Copy the lua scripts to the build directory
add_custom_target(copy_scripts
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy-scripts.cmake
)
add_dependencies(TowerDefense copy_scripts)