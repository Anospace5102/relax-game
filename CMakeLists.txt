cmake_minimum_required(VERSION 3.20) # CMake install : https://cmake.org/download/
project(relax_play LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_PREFIX_PATH "D:/Qt/6.9.1/mingw_64") # Qt Kit Dir
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

# Collect sources, headers, UI forms, and resource files
file(GLOB_RECURSE SOURCES 
    src/*.cpp include/*.h src/*.ui include/*.qrc
)

# Specify MSVC UTF-8 encoding   
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

add_executable(${PROJECT_NAME}
    # WIN32 # If you need a terminal for debug, please comment this statement //output --here!!!
    ${SOURCES}
    include/bullet.h 
) 

target_include_directories(${PROJECT_NAME}
    PRIVATE include
)

target_link_libraries(${PROJECT_NAME} 
    PRIVATE
        Qt::Core
        Qt::Widgets
)