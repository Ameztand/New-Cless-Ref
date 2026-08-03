#include "msgBoard.h"

const bool MsgData::getEsc(const int len) const
{
	return Esc == len;
}

const bool MsgData::getF1(const int len) const
{
	return F1 == len;
}

const bool MsgData::getMouseF() const
{
	return isMouseF;
}

const Position& MsgData::getMousePos() const
{
	return MousePos;
}

void MsgData::clear() {
	Esc = 0;
	F1 = 0;

	isMouseF = false;
	MousePos = Epos;
}