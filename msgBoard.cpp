#include "msgBoard.h"

const bool MsgData::getEsc(const int len) const
{
	return Esc.get(len);
}

const bool MsgData::getF1(const int len) const
{
	return F1.get(len);
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
	Esc.clear();
	F1.clear();

	isMouseF = false;
	MousePos = Epos;
}