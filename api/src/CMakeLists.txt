aux_source_directory(. SRC_LIST)    #搜索当前目录下的所有源文件，并加入SRC_LIST里面
include_directories(../include)     #添加头文件

add_library (api SHARED  ${SRC_LIST} ${INC_LIST})