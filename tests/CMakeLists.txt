# Tests
add_executable(tests LexerTests.cpp)

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.3.2)
FetchContent_MakeAvailable(Catch2)
target_link_libraries(tests PRIVATE lbc_lib project_options Catch2::Catch2WithMain)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
enable_testing()
catch_discover_tests(tests)
