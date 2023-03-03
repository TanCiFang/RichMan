#include "apiRegister.h"
#include <iostream>
#include<rttr/type>
#include <rttr/registration>
namespace tzyNet{

    //手动注册属性方法和构造函数
    RTTR_REGISTRATION
    {
        rttr::registration::class_<Activity>("Activity")
            .constructor<>()
            .method("gamePlay", &Activity::gamePlay);
    }

}

