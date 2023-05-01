cmake_minimum_required(VERSION 3.14)
project(TinyServer)

set(CMAKE_CXX_STANDARD 11)


include_directories(./include)

# 设置链接库
set(link_lib  pthread)


# 设置输出路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin) 

aux_source_directory(./source DIR_SOURCE)


add_executable(server ./main.cpp  ${DIR_SOURCE})

target_include_directories(server PUBLIC ./include)

target_link_libraries(server ${link_lib})
