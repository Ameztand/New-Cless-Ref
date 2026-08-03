#pragma once

struct StateTable {
	bool isLobby = false;
	bool isSelect = false;

	bool isDebug = false;//持续性
	bool LDebug = false;//持续性

	void clear() {
		isLobby = isSelect  = false;

	}
};