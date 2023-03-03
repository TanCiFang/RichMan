aux_source_directory(. SRC_LIST)    #搜索当前目录下的所有源文件，并加入SRC_LIST里面
include_directories(../include)     #添加头文件

add_executable(index.cgi ${SRC_LIST})

target_link_libraries(
    index.cgi 
    fcgi 
    fcgi++
    common
    api
    rttr_core
)