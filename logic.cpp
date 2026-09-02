#include "logic.h"

#include <memory>

#include "gameState.h"


void Logic::onEnter()
{
	data.initData();
	gameSta.initGameSta(data);
}

void Logic::tick(const IInputLayer::MsgData& out)
{
	//缓存输入数据到黑板
	data.pushMsgData(out);

	translateMsg();
	gameSta.getState()->tick(data, out);

	//换栈检查
	if (data.gameIntend.popSta)gameSta.popSta(data);
	else if (data.gameIntend.pushSelect) {
		gameSta.pushSta(data, std::make_unique<Select>());
	}
	else if (data.gameIntend.pushPause) {
		gameSta.pushSta(data, std::make_unique<Pause>());
	}
	else if (data.gameIntend.pushPuGame) {
		gameSta.pushSta(data, std::make_unique<PuGame>());
	}
	else if (data.gameIntend.rePuGame) {
		gameSta.popSta(data);//先退出暂停状态
		gameSta.popSta(data);
		gameSta.pushSta(data, std::make_unique<PuGame>());
	}
	else if (data.gameIntend.backLobby) {
		while (!(gameSta.getStaID() == IGameState::GameSta::Lobby)) {
			gameSta.popSta(data);
		}
	}
	//if (data.gameIntend.isEsc)gameSta.popSta(data);

	//数据清理
	if (data.gameIntend.initGameData)data.initGameData();
	if (data.gameIntend.initALLData)data.initData();
}

void Logic::translateMsg()
{
	const IInputLayer::MsgData& out = data.getMsgData();
	using KeySta = IInputLayer::KeySta;
	
	//data.gameIntend.isEsc = (out.Esc == KeySta::falling);
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

const RenderData& Logic::pushRender()
{
	tempRenderData.gameSta = gameSta.getStaID();
	tempRenderData.StaDepth = gameSta.getStaDepth();
	tempRenderData.isDebug = data.getF1debug();

	tempRenderData.piece = data.getPiece();
	tempRenderData.logicPiece = data.getLogicPiece();
	tempRenderData.selectingPos = data.getSelectingPos();
	tempRenderData.selectingCell = data.getSelectingCell();

	tempRenderData.CanCastling = { data.getCanCastling(1), data.getCanCastling(-1) };//传递列表

	tempRenderData.KingPos = data.getKingPos();
	tempRenderData.KingChecked = data.getKingChecked();
	tempRenderData.checkmate = data.getCheckmate();

	tempRenderData.mosuePos = data.getMsgData().MousePos;

	return tempRenderData;
}

void Logic::clearIntend()
{
	data.gameIntend = {};
}
