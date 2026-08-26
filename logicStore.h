#pragma once

#include "common.h"

#include "IInputLayer.h"

class Data {
private:
	int StaID = 1;
	int StaDepth = 1;

	IInputLayer::MsgData cacheMsgData;
public:
	const int getStaID()const;
	void setStaID(const int i);

	const int getStaDepth()const;
	void setStaDepth(const int i);

	const IInputLayer::MsgData& getMsgData()const;
	void pollMsgData(const IInputLayer::MsgData& out);

	void clearCacheData();

	void initData();
};



struct Intend {
	bool isExit = false;
	bool isPause = false;

	bool replaceSelect = false;

	

	void clear() {
		isExit = false;
		isPause = false;

		replaceSelect = false;
	}
};