#pragma once

#include "config_logic.h"

#include "IGameState.h"

struct RenderData {
	IGameState::GameSta gameSta= IGameState::GameSta::null;
	//IGameState::GameSta prveGameSta = IGameState::GameSta::null;//ÔÝÍ£ºó»æ»­±³¾°°å

	int StaDepth = 0;
	bool isDebug = false;//ÊÇ·ñË¢ÐÂdebug

	int bout = 1;//»ØºÏ

	Piece piece = {};
	LogicPiece logicPiece = {};
	Position selectingPos = Epos;
	Cell selectingCell = Ecell;

	Cell passedPawn = Ecell;
	Cell promotion = Ecell;//Éý±ä
	std::array<bool, 2>CanCastling = {};

	std::array<Position, 2>KingPos = {};
	Cell KingChecked = Ecell;
	int checkmate = 0;

	Position mosuePos = Epos;
};