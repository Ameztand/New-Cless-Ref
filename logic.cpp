#include "logic.h"


#include "msgBoard.h"
#include "renderBorad.h"

void Logic::onEnter()
{
	gameSta.initGameSta(ctx);
}

void Logic::tick(MsgData& msgData)
{
	translateMsg(msgData);
	if (intend.isExit)intend.isPause = gameSta.popSta(ctx);
	if (!intend.isPause) {

	}
}

void Logic::translateMsg(MsgData& msgData)
{
	intend.isExit = msgData.getEsc(1);
}

bool Logic::Exit()
{
	return gameSta.empty();
}

void Logic::pushRender(RenderState& renderSta)
{
	renderSta.isLobby = flag.isLobby;
}
