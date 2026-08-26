#pragma once

#include <cstdint>//？
#include "common.h" // 为了 Position 

class IInputLayer {
public:
    enum class KeySta : uint8_t {
        //表示持续状态

        null,//悬空
        falling, //下降沿
        Sdown,//短按
        Ldown,//长按
        rising//上升沿
    };

    struct MsgData {
        KeySta Esc = KeySta::null;
        KeySta F1 = KeySta::null;

        bool isMouseF = false;//鼠标左键
        Position MousePos = Epos;
    };

    virtual ~IInputLayer() = default;

    //读取并更新内部状态
    virtual void poll() = 0;

    virtual const IInputLayer::MsgData& getMsgData() const = 0;
};