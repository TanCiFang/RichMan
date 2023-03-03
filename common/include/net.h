#pragma once 

#include "nlohmann/json.hpp"
#include "common.h"
#include <string>
#include <string.h>
#include <vector>
#include <map>
#include <rttr/type>
#include <rttr/registration>

using json = nlohmann::json;

namespace tzyNet{

    /*
        URL解析类
    */
    class Url{
    public:
        int64_t sevId;
        int64_t uid;    //小于等于10位长度
        std::string ver;
        std::string token;
        std::string platform;

        Url(std::string url);
        
    private:
        enum paramType {
            Enum_SevId,     //服务器id
            Enum_Uid,       //用户uid
            Enum_Ver,       //版本
            Enum_Token,     //token
            Enum_Platform   //平台
        };

        std::string paramTypeName[5] = {
            "sevId",
            "uid",
            "ver",
            "token",
            "platform"
        };

        int _getParamPos(std::string& str, std::string paramName);
    };


    /*
        Client_JsonBuf解析类
    */
    class Request{
    public:
        std::string api;
        std::string ctrl;
        std::string param;

        Request(std::string& reqBuf);
    
    private:
        enum paramType {
            Enum_Api,
            Enum_Ctrl,
            Enum_Param
        };

        void _ini(std::string& reqBuf, int pos = 0);
    };

}