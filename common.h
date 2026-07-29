#pragma once

#include <Windows.h>
#include <array>

//==== 衡量表 ====
extern const int LOW_PRESS_TIME;//最短按下时间
extern const int PIECE_START_X;//棋盘左上角x坐标
extern const int PIECE_START_Y;//棋盘左上角y坐标
extern const int PIECE_CELL_SIZE;//棋盘格子大小

//extern const int dx[8], dy[8];//坐标偏移


// ==== 状态 ====(傻逼枚举)
extern const int STA_LOBBY;
extern const int STA_SELECT;
extern const int STA_PAUSE;
extern const int STA_PU_GAME;//双人模式

extern const RECT Larea, Marea, Rarea, Sarea, Parea;


//自定义类型（结构体）


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

struct DownMode {
    bool M = false;//刚按
    bool S = false;//短按
    bool L = false;//长按

private:
    using FieldPtr = bool DownMode::*;
    static constexpr FieldPtr table[3] = { &DownMode::M, &DownMode::S, &DownMode::L };

public:
    //enum class Mode : int { Idle = 0, Press = 1, Short = 2, Long = 3 };

    //访问
    bool get(int index) const {
        if (index == 0) {
            return !(M || S || L);
        }
        else if (index > 0 && index < 4) {
            return this->*table[index - 1];
        }
        return false;
    }

    //设置
    void set(int index) {
        if (index < 0 || index > 3) return; // 越界保护
        reset();
        if (index != 0) {
            this->*table[index - 1] = true;
        }
    }

    //清空
    void reset() {
        M = S = L = false;
    }
};

//坐标结构体（x, y）
struct Position {
    int x = 0;
    int y = 0;

    // 成员函数形式重载 ==
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
};

//单位坐标(-1,-1)
extern Position Epos;

//单元棋子对象
struct Cell {
    //棋子坐标
    int id = 0;
    Position pos = Epos;

    //是否移动过（为王、车使用，判定王车易位）
    bool hasMoved = false;

    // 成员函数形式重载 ==
    bool operator==(const Cell& other) const {
        return pos == other.pos;
    }
};

//单位棋子
extern Cell Ecless;

//鼠标按下情况（Sta,pos,仅Msg和Data）(鼠标没有3，一瞬间就会12)
struct MouseSta {
    int pressSta = 0;//按下情况
    Position pos = {};//鼠标坐标
};



//特殊类型数组


//棋盘[y][x]
using Piece = std::array<std::array<Cell, 8>, 8>;

//检查合法性的可移动棋盘
using LogicPiece = std::array<std::array<bool, 8>, 8>;

//默认棋盘ID表（初始化）白色在下
extern std::array<std::array<int, 8>, 8> EpieceID;

