#pragma once

#include "common.h"

struct Flag {
	bool isLobby = false;

	void clear() {
		isLobby = false;
	}
};

class Data {
private:

public:
};



struct Intend {
	bool isExit = false;
	bool isPause = false;


	void clear();
};