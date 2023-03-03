#include "net.h"

namespace tzyNet{

    /*
        URL解析类
    */
    Url::Url(std::string url){
        int pos = url.find("?");
        if (pos == std::string::npos) {
            Common::error("URL_CANT_DECODE");
        }

        std::string reqParams = url.substr(pos + 1);
        std::vector<std::string> arrParams = Common::strSplit(reqParams, "&");

        for(int i = 0; i < this->paramTypeName->length(); i++){
            std::string strParam = arrParams[i];
            int pos = _getParamPos(strParam, paramTypeName[i]);
            if(pos == -1){
                Common::error("URL_CANT_DECODE_" + strParam);
            }

            std::string strVal = strParam.substr(pos);
            
            switch (i){
                case Enum_SevId:
                    this->sevId = stoi(strVal);
                    break;

                case Enum_Uid:
                    this->uid = stoi(strVal);
                    break;

                case Enum_Ver:
                    this->ver = strVal;
                    break;

                case Enum_Token:
                    this->token = strVal;
                    break;

                case Enum_Platform:
                    this->platform = strVal;
                    break;
            }
        }
    }


    int Url::_getParamPos(std::string& str, std::string paramName){
        if(str.length() < paramName.length()){
            return -1;
        }

        paramName += "=";
        int pos = paramName.length();
        for(int i = 0; i < pos; i++){
            if(str[i] != paramName[i]){
                return -1;
            }
        }

        return pos;
    }


    /*
        Client_JsonBuf解析类
    */
    Request::Request(std::string& reqBuf){
        if(!json::accept(reqBuf)){
            Common::error("JSON_ERROR");
        }

        this->_ini(reqBuf);
    }

    void Request::_ini(std::string& reqBuf, int type){
        if(reqBuf.empty()){
            Common::error("REQUEST_EMPTY");
        }

        if(!json::accept(reqBuf)){
            return;
        }

        json js = json::parse(reqBuf);

        auto param = js.begin();
        auto val = param.value();
        std::string str = val.dump();
        
        switch (type){
            case this->Enum_Api:
                this->api = param.key();
                break;

            case this->Enum_Ctrl:
                this->ctrl = param.key();
                break;

            case this->Enum_Param:
                this->param = param.key();
                break;

            default:
                return;
        }

        this->_ini(str, type + 1);
    }


    RTTR_REGISTRATION
    {
    }
}
