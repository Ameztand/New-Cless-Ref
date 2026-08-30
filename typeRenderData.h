#pragma once

#include "config_logic.h"

#include "IGameState.h"

struct RenderData {
	IGameState::GameSta gameSta= IGameState::GameSta::null;
	//IGameState::GameSta prveGameSta = IGameState::GameSta::null;//ÔÝÍ£ºó»æ»­±³¾°°å

	int StaDepth = 0;
	bool isDebug = false;//ÊÇ·ñË¢ÐÂdebug

	Piece piece = {};
	LogicPiece logicPiece = {};
	Position selectingPos = Epos;
	Cell selectingCell = Ecell;

	Position mosuePos = Epos;
};