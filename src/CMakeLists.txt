set(SOURCE_LIST
    Game.cpp
    Gameobject.cpp
    MyEventReceiver.cpp
    WideText.cpp)

set(HEADER_LIST 
    "${TowerDefense_SOURCE_DIR}/include/Tower-defense-Lua/Game.h"
    "${TowerDefense_SOURCE_DIR}/include/Tower-defense-Lua/Gameobject.h"
    "${TowerDefense_SOURCE_DIR}/include/Tower-defense-Lua/MyEventReceiver.h"
    "${TowerDefense_SOURCE_DIR}/include/Tower-defense-Lua/WideText.h")

add_library(game_engine "${SOURCE_LIST}" "${HEADER_LIST}")

target_compile_definitions(game_engine PUBLIC RESOURCES_PATH="${PROJECT_SOURCE_DIR}/resources/")

target_include_directories(game_engine PUBLIC ../include)
target_include_directories(game_engine PUBLIC ${LUA_INCLUDE_DIR})

target_link_libraries(game_engine PUBLIC ${LUA_LIBRARIES} Irrlicht)

source_group(
    TREE "${PROJECT_SOURCE_DIR}/include"
    PREFIX "Header Files"
    FILES ${HEADER_LIST})