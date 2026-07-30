#pragma once


#include "common.h"
#include "context.h"

#include "gameBoard.h"
#include "gameStateMachine.h"
#include "msg.h"

class SysCommand;

class Logic {
private:
	Msg msg;
	MsgData msgData;

	Data data;
	Intend intend;
	GameCtx ctx = { data,intend };
	State gameSta;

public:
	void onEnter();

	void tick(SysCommand& sysCommand);

	void translateMsg(SysCommand& sysCommand);
};
