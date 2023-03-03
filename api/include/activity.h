#pragma once
#include <rttr/registration>
#include <rttr/type>

namespace tzyNet{
    
    /*
        活动接口类
    */
    class Activity
    {
    public:
        Activity();
        ~Activity();

        void gamePlay(int actId, std::string param);

        RTTR_ENABLE();
    private:

    };

}
