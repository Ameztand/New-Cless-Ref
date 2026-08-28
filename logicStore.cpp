#include "logicStore.h"

const IInputLayer::MsgData& Data::getMsgData()const {
	return cacheMsgData;
}

void Data::pushMsgData(const IInputLayer::MsgData& out) {
	cacheMsgData = out;
	//printf("%d,%d\n", cacheMsgData.MousePos.x, out.MousePos.x);
}

void Data::pushF1debug(bool purr, bool prve)
{
	F1debug = purr;
	prveF1debug = prve;
}

const bool Data::getF1debug()const {
	return F1debug;
}

const bool Data::getPrveF1debug() const
{
	return prveF1debug;
}

void Data::pushPiece(const Piece& out)
{
	piece = out;
}

void Data::pushPiece(const Cell& out, const Position& pos)
{
	piece[pos.y][pos.x] = out;
}

const Piece& Data::getPiece() const
{
	return piece;
}

void Data::pushSumiPiece(const Piece& out)
{
	sumiPiece = out;
}

void Data::pushSumiPiece(const Cell& out, const Position& pos)
{
	sumiPiece[pos.y][pos.x] = out;
}

const Piece& Data::getSumiPiece() const
{
	return sumiPiece;
}

void Data::pushLogicPiece(const LogicPiece& out)
{
	logicPiece = out;
}

void Data::pushLogicPiece(const bool& out, const Position& pos)
{
	logicPiece[pos.y][pos.x] = out;
}

const LogicPiece& Data::getLogicPiece() const
{
	return logicPiece;
}

void Data::initPiece()
{
	piece = {};
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			Cell p;
			p.pos = { i,j };
			int ID = EpieceID[j][i];
			if (ID != 0) {
				p.id = ID;
				//p.hasMoved = true;
			}
			piece[j][i] = p;
		}
	}
}

void Data::initSumiPiece()
{
	sumiPiece = piece;
}

void Data::initLogicPiece()
{
	logicPiece = {};
}

void Data::pushSelecting(const Cell& out)
{
	if (out == Ecell)return;
	for (int i = 0; i < 2; i++) {
		if (selecting[i] == Ecell)selecting[i] = out;
	}
}

void Data::pushSelecting(const Position& out)
{
	selectingPos = out;
}

const std::array<Cell, 2>& Data::getSelecting() const
{
	return selecting;
}

const Position& Data::getSelectingPos() const
{
	return selectingPos;
}

void Data::initSelecting()
{
	selecting[0] = selecting[1] = Ecell;
}

void Data::clearIntend()
{
	gameIntend = {};
}

void Data::initData()
{
	initGameData();

	clearIntend();
}

void Data::initGameData()
{
	initPiece();
	initSelecting();
	//printf("清理游戏数据\n");
}
