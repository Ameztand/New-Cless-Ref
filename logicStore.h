#pragma once

#include "common.h"

#include "IInputLayer.h"
#include "IGameState.h"

struct Intend {
	bool pushSelect = false;

	bool popSta = false;

	bool isEsc = false;
};


class Data {
private:
	using MsgData = IInputLayer::MsgData;
	using GameSta = IGameState::GameSta;

	MsgData cacheMsgData = {};

	bool F1debug = false;
	bool prveF1debug = false;

public:
	//游戏意图
	Intend gameIntend;

	//仅仅提交数据
	void pushMsgData(const MsgData& out);
	const MsgData& getMsgData()const;

	void pushF1debug(bool purr, bool prve);
	const bool getF1debug()const;
	const bool getPrveF1debug()const;

	//每帧调用
	void clearIntend();

	void initData();
};