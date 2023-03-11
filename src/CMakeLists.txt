# lbc library
add_library(
    lbc_lib
    Driver/Context.cpp
    Driver/Context.hpp
    Driver/Source.cpp
    Driver/Source.hpp
    Driver/SourceLoc.hpp
    Lexer/Lexer.cpp
    Lexer/Lexer.cpp
    Lexer/Token.cpp
    Lexer/Token.hpp
    pch.hpp
    Utils/Error.cpp
    Utils/Error.hpp
    Utils/StringContainers.hpp)

target_link_libraries(lbc_lib PRIVATE project_options project_warnings)
target_precompile_headers(lbc_lib PRIVATE pch.hpp)
target_include_directories(lbc_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(lbc_lib PRIVATE "${CMAKE_BINARY_DIR}/configured_files/include")

# lbc executable
add_executable(lbc main.cpp)
target_link_libraries(lbc PRIVATE lbc_lib project_options project_warnings)
set_target_properties(lbc PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
