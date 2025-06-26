# ./yacc/CMakeLists.txt - 词法和语法分析器模块

# 查找Bison和Flex工具
find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

# 定义输入和输出文件
set(PARSER_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/parser.y)
set(LEXER_INPUT ${CMAKE_CURRENT_SOURCE_DIR}/lex.l)

# 使用Bison生成语法分析器
BISON_TARGET(Parser ${PARSER_INPUT} ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hpp)

# 使用Flex生成词法分析器  
FLEX_TARGET(Scanner ${LEXER_INPUT} ${CMAKE_CURRENT_BINARY_DIR}/scanner.cpp
    DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/scanner.hpp)

# 确保词法分析器在语法分析器之后生成（因为它需要parser.hpp）
ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

# 创建库，只包含自动生成的源文件
add_library(Yacc 
    ${BISON_Parser_OUTPUTS}
    ${FLEX_Scanner_OUTPUTS}
)

# 链接依赖
target_link_libraries(Yacc Lib)

# 包含目录
target_include_directories(Yacc PUBLIC 
    ${PROJECT_SOURCE_DIR}/lib
    ${CMAKE_CURRENT_BINARY_DIR}  # 包含自动生成的头文件
    ${CMAKE_CURRENT_SOURCE_DIR}   # 包含原始的.y和.l文件
)