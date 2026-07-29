#include "msg.h"

#include "common.h"




void Msg::push(MsgData& msgData)
{
    msgData.Esc.set(keySta_[VK_ESCAPE]);
    msgData.F1.set(keySta_[VK_F1]);

    msgData.isMouseF = (mouesDown_.getPressSta() == 0 ? false : true);
    msgData.MousePos = mousePos_;

    //printf("提交msg\n");
}

// ========== 监听层 ===========
void Msg::GetMsg(MsgData& msgData) {
    //处理队列写入缓冲
    while (peekmessage(&msg_, EX_MOUSE | EX_KEY)) {
        if (msg_.message == WM_KEYDOWN) {
            tempKeys_[msg_.vkcode] = true;
        }
        else if (msg_.message == WM_KEYUP) {
            if (msg_.vkcode >= 0 && msg_.vkcode < 256) {
                tempKeys_[msg_.vkcode] = false;
            }
        }
        else if (msg_.message == WM_LBUTTONDOWN) {
            tempMouse_ = true;
        }
        else if (msg_.message == WM_LBUTTONUP) {
            tempMouse_ = false;
        }
        else if (msg_.message == WM_MOUSEMOVE) {
            mousePos_ = { msg_.x, msg_.y };
        }
    }

    //统一写入数组

    //键盘
    for (int i = 0; i < 256; i++) {
        auto it = keys_.find(i);
        if (it == keys_.end()) continue;
        if (tempKeys_[i]) {
            it->second.pressSta.update(true);//按下状态更新

            int pressSta_ = it->second.pressSta.getPressSta();//获取按下状态
            if (pressSta_ == 1) it->second.pressTime_ = std::chrono::steady_clock::now();//记录当下的时间戳

            auto now = std::chrono::steady_clock::now();//当下的时间戳
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - it->second.pressTime_).count();//计算按下时长
            bool pressLong_ = duration >= LOW_PRESS_TIME ? true : false;//受否长按

            //按下数字情况处理（0没按 1刚按 2短按 3长按 4刚放）
            int res = 0;
            if (pressSta_ == 0 || pressSta_ == 1) {
                res = pressSta_;
            }
            else if (pressSta_ == 3) {
                res = pressSta_ + (pressLong_ ? 0 : -1);
            }
            else if (pressSta_ == 2) {
                res = 4;
            }

            keySta_[i] = res;
        }
        else {
            it->second.pressSta.update(false);//按下状态更新
            int pressSta_ = it->second.pressSta.getPressSta();//获取按下状态

            keySta_[i] = pressSta_ == 2 ? 4 : 0;
        }
    }
    //鼠标
    mouesDown_.update(tempMouse_);

    //统一写入黑板
    push(msgData);

    //清空临时数据
    for (int i = 0; i < 256; i++) {
        //tempKeys_[i] = {};
        //tempMouse_ = false;
    }
}

void Msg::initMsg()
{
    for (int i = 0; i < 256; i++) {
        keys_[i] = {};
        keySta_[i] = 0;
    }
    mouesDown_ = {};
    mousePos_ = {};

}


