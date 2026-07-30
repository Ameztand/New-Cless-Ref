#include "logic.h"

#include "sysCommand.h"

void Logic::onEnter()
{
	msg.initMsg();
	gameSta.initGameSta(ctx);
}

void Logic::tick(SysCommand& sysCommand)
{
	msg.GetMsg(msgData);
	translateMsg(sysCommand);
}

void Logic::translateMsg(SysCommand& sysCommand)
{
	sysCommand.setExit(msgData.getEsc(1));
}
