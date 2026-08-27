#pragma once

#include "common.h"

extern const int LOW_PRESS_TIME;

//双缓冲bool(prev,curr)
struct DoubleBool {
    bool prev = false;
    bool curr = false;

    // 成员函数形式重载 ==
    bool operator==(const DoubleBool& other) const {
        return prev == other.prev && curr == other.curr;
    }

    //更新
    void update(bool newCurr) {
        prev = curr;
        curr = newCurr;
    }

    //检查按下情况（00/0没按 01/1刚按 11/3在按 10/2刚松）0132
    int getPressSta() {
        int res = 0;
        if (prev)res += 2;
        if (curr)res += 1;
        return res;
    }
};

//鼠标按下情况（Sta,pos,仅Msg和Data）(鼠标没有3，一瞬间就会12)
struct MouseSta {
    int pressSta = 0;//按下情况
    Position pos = {};//鼠标坐标
};