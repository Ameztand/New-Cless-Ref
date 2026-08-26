#pragma once

#include "IInputLayer.h"

class MsgStore {
private:
	//IInputLayer::KeySta keySta;
	IInputLayer::MsgData msgData;
public:
	const IInputLayer::MsgData& getMsgData() const;
	void setMsgData(const IInputLayer::MsgData& out);

	void clear();
};
