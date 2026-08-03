#include "logic.h"

#include <memory>

#include "msgBoard.h"
#include "gameState.h"


void Logic::onEnter()
{
	gameSta.initGameSta(ctx);
}

void Logic::tick(MsgData& msgData)
{
	translateMsg(msgData);
	if (intend.isExit)intend.isPause = gameSta.popSta(ctx);
	if (!intend.isPause) {
		//Õ»¶¥
		gameSta.getState()->tick(ctx, msgData);

		//»»Õ»
		if (intend.replaceSelect) {
			gameSta.pushSta(ctx, std::make_unique<Select>());
			updateSta();
		}
	}

}

void Logic::translateMsg(MsgData& msgData)
{
	intend.isExit = msgData.getEsc(1);

	flag.isDebug = translateDebug(msgData);
}

bool Logic::translateDebug(MsgData& msgData)
{
	if (msgData.getF1(1)) {
		flag.isDebug = !flag.isDebug;
		printf("ÇÐ»»\n");
	}
	else if (msgData.getF1(3)) { 
		flag.LDebug = true;
		printf("3");
	}
	else if (msgData.getF1(4) && flag.LDebug) {
		flag.LDebug = false;
		flag.isDebug = !flag.isDebug;
		printf("4\n");
	}

	return (flag.isDebug || flag.LDebug);
}

bool Logic::Exit()
{
	return gameSta.empty();
}

void Logic::pushRender(StateTable& renderSta)
{
	renderSta = flag;
}

const GameCtx& Logic::pushCtx()
{
	return ctx;
}

void Logic::clearIntend()
{
	intend.clear();
}

void Logic::updateSta()
{
	data.setStaID(gameSta.getStaID());
	data.setStaDepth(gameSta.getStaID());
}
