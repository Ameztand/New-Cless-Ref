#include "logicStore.h"

const IInputLayer::MsgData& Data::getMsgData()const {
	return cacheMsgData;
}

void Data::pushMsgData(const IInputLayer::MsgData& out) {
	cacheMsgData = out;
	//printf("%d,%d\n", cacheMsgData.MousePos.x, out.MousePos.x);
}

void Data::pushF1debug(bool purr, bool prve)
{
	F1debug = purr;
	prveF1debug = prve;
}

const bool Data::getF1debug()const {
	return F1debug;
}

const bool Data::getPrveF1debug() const
{
	return prveF1debug;
}

void Data::clearIntend()
{
	gameIntend = {};
}

void Data::initData()
{
	MsgData cacheMsgData = {};
	GameSta cacheGameSta = GameSta::null;
	int StaDepth = 1;

	clearIntend();
}
