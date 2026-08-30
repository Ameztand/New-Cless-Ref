#pragma once

#include "config_logic.h"

#include "IInputLayer.h"
#include "IGameState.h"

struct Intend {
	bool pushSelect = false;
	bool pushPause = false;
	bool pushPuGame = false;

	bool backLobby = false;
	bool rePuGame = false;

	bool popSta = false;

	bool initGameData = false;
	bool initALLData = false;
};


class Data {
private:
	using MsgData = IInputLayer::MsgData;
	//using GameSta = IGameState::GameSta;

	MsgData cacheMsgData = {};

	//F1Debug
	bool F1debug = false;
	bool prveF1debug = false;



	Piece piece = {};//真实位置
	Piece sumiPiece = {};//模拟位置
	LogicPiece logicPiece = {};//可移动棋盘

	Position selectingPos = Epos;//鼠标悬浮
	Cell selectingCell = Ecell;//执棋

public:
	//游戏意图
	Intend gameIntend;

	//输入
	void pushMsgData(const MsgData& out);
	const MsgData& getMsgData()const;

	//Debug
	void pushF1debug(bool purr, bool prve);
	const bool getF1debug()const;
	const bool getPrveF1debug()const;

	//三个棋盘数据   整体/单独提交重载
	void pushPiece(const Piece& out);
	void pushPiece(const Cell& out, const Position& pos);
	const Piece& getPiece()const;
	const Cell& getPiece(const Position& pos)const;
	void pushSumiPiece(const Piece& out);
	void pushSumiPiece(const Cell& out, const Position& pos);
	const Piece& getSumiPiece()const;
	const Cell& getSumiPiece(const Position& pos)const;
	void pushLogicPiece(const LogicPiece& out);
	void pushLogicPiece(const Position& pos, const bool& out);
	const LogicPiece& getLogicPiece()const;
	const bool& getLogicPiece(const Position& pos)const;
	void initPiece();
	void initSumiPiece();
	void initLogicPiece();

	//自动推导
	void pushSelectingCell(const Cell& out);
	void pushSelectingPos(const Position& out);
	const Cell& getSelectingCell()const;
	const Position& getSelectingPos()const;
	void initSelecting();

	//每帧调用，清理意图
	void clearIntend();

	void initData();//清理总数据
	void initGameData();
};