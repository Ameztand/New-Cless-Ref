#include "logic.h"

#include <memory>

#include "gameState.h"


void Logic::onEnter()
{
	gameSta.initGameSta(data);
}

void Logic::tick(const IInputLayer::MsgData& out)
{
	//初步翻译全局热键
	data.pushMsgData(out);
	translateMsg();

	//执行栈顶
	gameSta.getState()->tick(data, out);

	//换栈检查
	if (data.gameIntend.popSta)gameSta.popSta(data);
	else if (data.gameIntend.pushSelect) {
		gameSta.pushSta(data, std::make_unique<Select>());
	}

	if (data.gameIntend.isEsc)gameSta.popSta(data);
}

void Logic::translateMsg()
{
	const IInputLayer::MsgData& out = data.getMsgData();
	using KeySta = IInputLayer::KeySta;
	
	data.gameIntend.isEsc = (out.Esc == KeySta::falling);
	translateDebug();
}

void Logic::translateDebug()
{
	const IInputLayer::MsgData& out = data.getMsgData();
	using KeySta = IInputLayer::KeySta;

	bool prve = data.getPrveF1debug();
	bool purr = false;

	if (out.F1 == KeySta::falling) {
		prve = !prve;
		//printf("单击开\n");
	}
	if (out.F1 == KeySta::Ldown) {
		prve = false;
		//printf("单击关\n");
	}
	if (!(out.F1 == KeySta::null)) {
		purr = true;
	}

	data.pushF1debug((prve || purr), prve);
}

bool Logic::Exit()
{
	return gameSta.empty();
}

const RenderData Logic::pushRender()
{
	RenderData tempRenderData;

	tempRenderData.gameSta = gameSta.getStaID();
	tempRenderData.StaDepth = gameSta.getStaDepth();
	tempRenderData.isDebug = data.getF1debug();

	return tempRenderData;
}

void Logic::clearIntend()
{
	data.gameIntend = {};
}
