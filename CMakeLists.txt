cmake_minimum_required(VERSION 3.16)
project(GomokuAI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML 路径
set(SFML_DIR "D:/Dev/SFML-2.6.1/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# 添加源文件
set(SOURCES
    src/core/GameEngine.cpp
    src/heuristics/Heuristics.cpp
    src/ai/MinimaxAI.cpp
    src/ai/AlphaBetaAI.cpp
    src/gui/BoardView.cpp
    src/gui/Main.cpp
)

# 创建可执行文件
add_executable(Gomoku ${SOURCES})

# 包含头文件路径
target_include_directories(Gomoku PRIVATE
    ${PROJECT_SOURCE_DIR}/src
    ${SFML_INCLUDE_DIR}
)

# 链接 SFML 库
target_link_libraries(Gomoku PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)

# 假设你的 assets 文件夹在源目录下
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets")

# 在每次构建后把 assets 复制到输出目录（Debug/Release）
add_custom_command(TARGET Gomoku POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${ASSETS_DIR}"
    $<TARGET_FILE_DIR:Gomoku>/assets
)
