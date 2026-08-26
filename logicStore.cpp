#include "logicStore.h"

const int Data::getStaID()const {
	return StaID;
}

void Data::setStaID(const int i)
{
	StaID = i;
}

const int Data::getStaDepth()const {
	return StaDepth;
}

void Data::setStaDepth(const int i)
{
	StaDepth = i;
}

const IInputLayer::MsgData& Data::getMsgData()const {
	return cacheMsgData;
}

void Data::pollMsgData(const IInputLayer::MsgData& out) {
	cacheMsgData = out;
}

void Data::clearCacheData() {
	cacheMsgData = {};
}