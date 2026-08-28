#pragma once

#include <Windows.h>
#include <array>

//点击区域
extern const int LOW_PRESS_TIME;
extern const int PIECE_START_X;//棋盘左上角x坐标
extern const int PIECE_START_Y;//棋盘左上角y坐标
extern const int PIECE_CELL_SIZE;//棋盘格子大小

extern const RECT Larea, Marea, Rarea, Sarea, Parea;

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