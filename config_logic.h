#pragma once

#include <array>

#include "common.h"

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

//特殊类型数组


//棋盘[y][x]
using Piece = std::array<std::array<Cell, 8>, 8>;

//检查合法性的可移动棋盘
using LogicPiece = std::array<std::array<bool, 8>, 8>;

//默认棋盘ID表（初始化）白色在下
extern std::array<std::array<int, 8>, 8> EpieceID;
