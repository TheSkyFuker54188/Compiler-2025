cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -lm -g") # 添加-g用于调试

project(SysY_Frontend VERSION 0.1.0 LANGUAGES C CXX)

# 生成compile_commands.json，方便IDE和工具使用
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 前端的头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include/lib)
include_directories(${CMAKE_SOURCE_DIR}/include/yacc)
include_directories(${CMAKE_BINARY_DIR}/yacc)  # 包含自动生成的头文件

# 添加前端组件的子目录（注意顺序：先yacc后lib，因为lib可能依赖yacc生成的文件）
add_subdirectory(${PROJECT_SOURCE_DIR}/yacc)    # 词法分析器和语法分析器
add_subdirectory(${PROJECT_SOURCE_DIR}/lib)     # AST节点实现

# 添加可执行文件 - 这是我们的前端解析器
add_executable(frontend_parser main.cpp)

# 链接库
target_link_libraries(frontend_parser Yacc Lib)

# 目标包含目录
target_include_directories(frontend_parser PRIVATE 
    ${PROJECT_SOURCE_DIR}/yacc
    ${PROJECT_SOURCE_DIR}/lib
    ${CMAKE_BINARY_DIR}/yacc  # 自动生成的头文件目录
)

# 警告标志 - 忽略未使用变量的警告(在开发阶段比较有用)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable")
