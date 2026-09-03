#pragma once

#include <easyx.h>

#include "typeRenderData.h"

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

	RenderData renderData = {};
	IGameState::GameSta prveGameSta = IGameState::GameSta::null;//暂停后绘画背景板

public:
	//渲染双人
	void renderPuGame();

	void renderGG();
	void renderPromotion();
	void renderBout();

	//渲染暂停
	void renderPause();

	//渲染选择难度
	void renderSelect();

	//渲染大厅
	void renderLobby();

	//调试渲染
	void renderDebug();

	void render(const RenderData& out);

	//初始化界面
	void initEasyX();
};

//===== 辅助函数 =====
//void renderRectangle(const renderSelectingRrec::ModeSta modeSta);
