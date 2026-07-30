#pragma once

#include "common.h"

class Msg;

class MsgData {
private:
	//m瞬间按下 S短按 L长按
	DownMode Esc = {};
	DownMode F1 = {};

	bool isMouseF = false;
	Position MousePos = Epos;

	friend class Msg;

public:
	const bool getEsc(const int len)const;
	const bool getF1(const int len)const;
	const bool getMouseF()const;
	const Position& getMousePos()const;

	void clear();
};
