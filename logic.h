#pragma once


#include "common.h"
#include "context.h"

#include "gameBoard.h"
#include "gameStateMachine.h"

#include "StateTable.h"



class MsgData;
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

	void tick(MsgData& msgData);

	void translateMsg(MsgData& msgData);

	bool translateDebug(MsgData& msgData);
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
