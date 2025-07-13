find_package(Catch2 3 REQUIRED)

add_executable(tests test.cpp)
target_link_libraries(tests PUBLIC game_engine Catch2::Catch2WithMain)
include(Catch)
catch_discover_tests(tests)
