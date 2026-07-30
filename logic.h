#pragma once


#include "common.h"
#include "context.h"

#include "gameBoard.h"
#include "gameStateMachine.h"



class MsgData;
class RenderState;



class Logic {
private:
	Flag flag;

	Data data;
	Intend intend;
	GameCtx ctx = { data,intend,flag };

	State gameSta;

public:
	void onEnter();

	void tick(MsgData& msgData);

	void translateMsg(MsgData& msgCommand);

	bool Exit();

	void pushRender(RenderState& renderSta);
};
