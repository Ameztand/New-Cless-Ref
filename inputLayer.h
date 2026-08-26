#pragma once

#include "IInputLayer.h"

#include "msg.h"
#include "msgStore.h"


class InputLayer :public IInputLayer {
private:
    Msg msg;
    //KeySta keySta;
    MsgStore msgStore;

public:
    InputLayer() = default;
    virtual ~InputLayer() = default;

    // 读取并更新内部状态
    void poll() override;

    //获取快照
    const IInputLayer::MsgData& getMsgData() const override;

    void initInputLayer();

};
