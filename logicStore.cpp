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

const Cell& Data::getPiece(const Position& pos) const
{
	return piece[pos.y][pos.x];
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

const Cell& Data::getSumiPiece(const Position& pos) const
{
	return pos == Epos ? Ecell : sumiPiece[pos.y][pos.x];
}

void Data::pushLogicPiece(const LogicPiece& out)
{
	logicPiece = out;
}

void Data::pushLogicPiece(const Position& pos, const bool& out)
{
	logicPiece[pos.y][pos.x] = out;
}

const LogicPiece& Data::getLogicPiece() const
{
	return logicPiece;
}

const bool& Data::getLogicPiece(const Position& pos) const
{
	return logicPiece[pos.y][pos.x];
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

void Data::pushSelectingCell(const Cell& out)
{
	selectingCell = out;
}

void Data::pushSelectingPos(const Position& out)
{
	selectingPos = out;
}

const Cell& Data::getSelectingCell() const
{
	return selectingCell;
}

const Position& Data::getSelectingPos() const
{
	return selectingPos;
}

void Data::initSelecting()
{
	selectingPos = Epos;
	selectingCell = Ecell;
}

void Data::pushKingPos(const Position& pos, const int camp)
{
	int i = (camp == 1 ? 0 : 1);
	KingPos[i] = pos;
}

const std::array<Position, 2>& Data::getKingPos() const
{
	return KingPos;
}

const Position& Data::getKingPos(const int camp) const
{
	int i = (camp == 1 ? 0 : 1);
	return KingPos[i];
}

void Data::initKingPos()
{
	KingPos[0] = { 4,7 };
	KingPos[1] = { 4,0 };
}

void Data::pushKingChecked(const Cell& out)
{
	if (KingChecked == Ecell)KingChecked = out;
}

const Cell& Data::getKingChecked() const
{
	return KingChecked;
}

void Data::initKingChecked()
{
	KingChecked = Ecell;
}

void Data::pushCheckmate(const int camp)
{
	checkmate = camp;
}

const int Data::getCheckmate() const
{
	return checkmate;
}

void Data::initCheckmate()
{
	checkmate = 0;
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
	initLogicPiece();

	initKingPos();
	initKingChecked();

	initCheckmate();
	//printf("清理游戏数据\n");
}
