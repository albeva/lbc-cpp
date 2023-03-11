# lbc library
add_library(
    lbc_lib
    pch.hpp
    Lexer/Lexer.cpp
    Lexer/Lexer.cpp
)

target_link_libraries(lbc_lib PRIVATE project_options project_warnings)
target_precompile_headers(lbc_lib PRIVATE pch.hpp)
target_include_directories(lbc_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(lbc_lib PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

# lbc executable
add_executable(lbc main.cpp)
target_link_libraries(lbc PRIVATE lbc_lib)
set_target_properties(lbc PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
