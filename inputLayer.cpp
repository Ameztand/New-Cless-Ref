#include "inputLayer.h"



void InputLayer::poll()
{
	msg.GetMsg();
	msgStore.setMsgData(msg.push());

	//printf("–¥»Îmsg,(%d,%d)\n", msgStore.getMsgData().MousePos.x, msgStore.getMsgData().MousePos.y);
}


const IInputLayer::MsgData& InputLayer::getMsgData() const
{
	return msgStore.getMsgData();
}

void InputLayer::initInputLayer()
{
	msg.initMsg();
	msgStore.clear();
}
