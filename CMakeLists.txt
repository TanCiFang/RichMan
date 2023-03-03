cmake_minimum_required(VERSION 3.9)
SET( CMAKE_CXX_FLAGS "-std=c++11 -O3")
PROJECT(TZYSERVER)

SET(TZYNET_LIB ${PROJECT_SOURCE_DIR}/lib/libSrc)

#被链接的库相对路径
link_directories(/usr/lib64)
#被链接库的头文件相对路径
include_directories(
    /usr/local/include/
    public/include
    common/include
    api/include
)

# 递归包含头文件的函数
function(include_sub_directories_recursively root_dir)
    if (IS_DIRECTORY ${root_dir})               # 当前路径是一个目录吗，是的话就加入到包含目录
        #        if (${root_dir} MATCHES "include")
        message("INC: " ${root_dir})
        include_directories(${root_dir})
        #        endif()
    endif()

    file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*) # 获得当前目录下的所有文件，让如ALL_SUB列表中
    foreach(sub ${ALL_SUB})
        if (IS_DIRECTORY ${root_dir}/${sub})
            include_sub_directories_recursively(${root_dir}/${sub}) # 对子目录递归调用，包含
        endif()
    endforeach()
endfunction()

# 递归包含工程文件夹下的头文件，这里直接把CMakelist.txt所在文件夹下的文件夹都包含
include_sub_directories_recursively(${TZYNET_LIB})

LINK_DIRECTORIES(${TZYNET_LIB}/rttr/lib64)

ADD_SUBDIRECTORY(api)
ADD_SUBDIRECTORY(public)
ADD_SUBDIRECTORY(common)
# ADD_SUBDIRECTORY(controller)
# ADD_SUBDIRECTORY(model)
