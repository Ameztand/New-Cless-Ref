#pragma once

#include "config_logic.h"

#include "IGameState.h"

struct RenderData {
	IGameState::GameSta gameSta= IGameState::GameSta::null;
	int StaDepth = 0;
	bool isDebug = false;//ÊÇ·ñË¢ÐÂdebug

	Piece piece = {};

	Position mosuePos = Epos;
};