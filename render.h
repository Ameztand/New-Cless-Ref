#pragma once

#include <easyx.h>

#include "context.h"

class RenderState;

class Renderer {
private:

	//颜色数组
	COLORREF colors[2] = {
		RGB(255, 255, 255),//白
		RGB(255, 189, 0)   //橙
	};

	// 棋子字符映射：索引0-12，0-5黑棋，6为空 7-12白棋
	const wchar_t* pieceChar[13] = {
		L"♟", L"♜", L"♞", L"♝", L"♛", L"♚",   // 0-5 黑 兵车马象后王
		L" ",                                       // 6 空
		L"♔", L"♕", L"♗", L"♘", L"♖", L"♙"    // 7-12 白 王后象马车兵
	};

public:
	//渲染双人
	void renderPUgame(GameCtx& ctx);

	//渲染选择难度
	void renderSelect();

	//渲染大厅
	void renderLobby();

	//调试渲染
	void renderDebug(GameCtx& ctx);

	void render(RenderState& renderSta);

	//初始化界面
	void initEasyX();
};
