#pragma once

#include "common.h"


class Data {
private:
	int StaID = 1;
	int StaDepth = 1;
public:
	const int getStaID()const;
	void setStaID(const int i);

	const int getStaDepth()const;
	void setStaDepth(const int i);

	void initData();
};



struct Intend {
	bool isExit = false;
	bool isPause = false;

	bool replaceSelect = false;

	

	void clear() {
		isExit = false;
		isPause = false;

		replaceSelect = false;
	}
};