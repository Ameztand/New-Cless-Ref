#pragma once


#include "common.h"
#include "context.h"

#include "logicStore.h"
#include "gameStateMachine.h"

#include "StateTable.h"

#include"IInputLayer.h"



struct StateTable;



class Logic {
private:
	StateTable flag;

	Data data;
	Intend intend;
	GameCtx ctx = { data,intend,flag };

	State gameSta;

public:
	void onEnter();

	void tick(const IInputLayer::MsgData& out);

	void translateMsg();

	bool translateDebug();

	//检查ESC退出
	bool Exit();
	//提交渲染数据
	void pushRender(StateTable& renderSta);
	//提供黑板数据
	const GameCtx& pushCtx();
	//清理意图管线
	void clearIntend();
	//更像栈状态
	void updateSta();

};
