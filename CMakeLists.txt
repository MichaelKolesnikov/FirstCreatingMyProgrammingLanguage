cmake_minimum_required(VERSION 3.21)

project(GraphProject VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main
    main.cpp
    Lexer.cpp
    Parser.cpp
    ast/BinaryExpression.cpp
    ast/WordExpression.cpp
    ast/NumberExpression.cpp
    ast/UnaryExpression.cpp
)

target_include_directories(main PRIVATE
    ${PROJECT_SOURCE_DIR}
)
