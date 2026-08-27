#include "common.h"

//==== 衡量表 ====
const  int LOW_PRESS_TIME = 200;
const  int PIECE_START_X = 75;
const  int PIECE_START_Y = 75;
const  int PIECE_CELL_SIZE = 60;

const  RECT Larea = { 362, 402, 458, 448 };//左按钮
const  RECT Marea = { 492, 402, 588, 448 };//中按钮
const  RECT Rarea = { 622, 402, 718, 448 };//右按钮
const  RECT Sarea = { 492, 502, 588, 548 };//开始按钮
const  RECT Parea = { PIECE_START_X, PIECE_START_Y, PIECE_START_X + 8 * PIECE_CELL_SIZE, PIECE_START_Y + 8 * PIECE_CELL_SIZE };//棋盘

//单位坐标
Position Epos = { -1,-1 };