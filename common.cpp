#include "common.h"

//==== 衡量表 ====
const  int LOW_PRESS_TIME = 200;
const  int PIECE_START_X = 75;
const  int PIECE_START_Y = 75;
const  int PIECE_CELL_SIZE = 60;

//const int dx[8] = { 0,1,1,1,0,-1,-1,-1 };
//const int dy[8] = { -1,-1,0,1,1,1,0,-1 };

// ==== 状态 ====（傻逼枚举！！！！！！！！！！！）
const  int STA_LOBBY = 1;
const  int STA_SELECT = 2;
const  int STA_PAUSE = 3;
const  int STA_PU_GAME = 4;//双人模式

const  RECT Larea = { 362, 402, 458, 448 };//左按钮
const  RECT Marea = { 492, 402, 588, 448 };//中按钮
const  RECT Rarea = { 622, 402, 718, 448 };//右按钮
const  RECT Sarea = { 492, 502, 588, 548 };//开始按钮
const  RECT Parea = { PIECE_START_X, PIECE_START_Y, PIECE_START_X + 8 * PIECE_CELL_SIZE, PIECE_START_Y + 8 * PIECE_CELL_SIZE };//棋盘

//默认棋盘ID表（初始化）白色在下
std::array<std::array<int, 8>, 8> EpieceID = { {
        {{ -5, -4, -3, -2, -1, -3, -4, -5 }},
        {{ -6, -6, -6, -6, -6, -6, -6, -6 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 0, 0, 0, 0, 0, 0, 0, 0 }},
        {{ 6, 6, 6, 6, 6, 6, 6, 6 }},
        {{ 5, 4, 3, 2, 1, 3, 4, 5 }}
    } };






//单位坐标
Position Epos = { -1,-1 };

//单位棋子
Cell Ecless = { 0,Epos,false };