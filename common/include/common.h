#pragma once

#include <stdlib.h>
#include <unistd.h>
#include "fcgio.h"
#include "fcgi_config.h"  // HAVE_IOSTREAM_WITHASSIGN_STREAMBUF

//tzy
#include <vector>
#include <string>


#include "apiRegister.h"
#include "comRegister.h"

extern char ** environ;

namespace tzyNet{
    // Maximum number of bytes allowed to be read from stdin
    static const unsigned long STDIN_MAX = 1000000;

    void printEnvList(const char * const * envp);

    long gstdin(FCGX_Request * request, char ** content);

    class Common{
    public:
        static void error(std::string msg){
            //暂未完善
            std::cout << "error:" + msg << std::endl;
            exit(EXIT_FAILURE);
        }

        // 字符串分割
        static std::vector<std::string> strSplit(const std::string &str, const std::string &pattern);
    };


}
