#include "msgStore.h"

const IInputLayer::MsgData& MsgStore::getMsgData() const {
	return msgData;
}

void MsgStore::setMsgData(const IInputLayer::MsgData& out)
{
	msgData = out;
}

void MsgStore::clear() {
	msgData = {};
}