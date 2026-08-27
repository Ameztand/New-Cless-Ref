#pragma once


#include <chrono>
#include <map>
#include <easyx.h>
#include <array>

#include "IInputLayer.h"
#include "config_msg.h"

// ========== 监听层 ===========
class Msg {
private:
    //临时缓冲键盘按下数组
    bool tempKeys_[256] = {  };

    //临时缓冲鼠标按下
    bool tempMouse_ = false;

    //键盘按下情况
    struct keySta {
        std::chrono::steady_clock::time_point pressTime_;//按下时间戳
        DoubleBool pressSta;//按下情况
    };

    //键盘按下情况表(键名、按下时间戳、按下情况)
    std::map<int, keySta> keys_ = {};

    //键盘按下情况
    std::array<int, 256>keySta_ = {};

    //消息结构体
    ExMessage msg_;

    //鼠标按下情况
    DoubleBool mouesDown_ = {};

    //光标坐标
    Position mousePos_;

public:
    //返回提交数据
    const IInputLayer::MsgData push();

    //鼠标键盘监听处理
    void GetMsg();

    //初始化（自动注册）
    void initMsg();
};

