#include "gameState.h"

//#include <memory>

#include "logicStore.h"
#include "typeRenderData.h"

namespace HandleInput{
    bool EscPop(Data& data, const IInputLayer::MsgData& out)
    {
        using KeySta = IInputLayer::KeySta;
        bool temp = (out.Esc == KeySta::falling);
        data.gameIntend.popSta = temp;
        return temp;
    }

    bool EscPuase(Data& data, const IInputLayer::MsgData& out)
    {
        using KeySta = IInputLayer::KeySta;
        bool temp = (out.Esc == KeySta::falling);
        data.gameIntend.pushPause = temp;
        return temp;
    }

    bool Clickbotton(const RECT& area, const Position& pos) {
        return (pos.x >= area.left && pos.x <= area.right && pos.y >= area.top && pos.y <= area.bottom);
    }

    Position mousePosToPiecePos(const Position& pos)
    {
        if (pos.x > Parea.left && pos.x < Parea.right && pos.y > Parea.top && pos.y < Parea.bottom) {
            int col = (pos.x - PIECE_START_X) / PIECE_CELL_SIZE;
            int row = (pos.y - PIECE_START_Y) / PIECE_CELL_SIZE;
            //printf("%d %d\n", col, row);
            const Position res = { col,row };
            return res;
        }
        return Epos;
    }
}

namespace PosOffset {
    Position posMoveNormal(const Position& pos, int dir)
    {
        const int dx[8] = { 0,1,1,1,0,-1,-1,-1 };
        const int dy[8] = { -1,-1,0,1,1,1,0,-1 };

        int x = pos.x + dx[dir];
        int y = pos.y + dy[dir];

        if (0 <= x && x <= 7 && 0 <= y && y <= 7) {
            return { x,y };
        }
        return Epos;
    }

    Position posMoveKnight(const Position& pos, int dir)
    {
        const int Kdx[8] = { -1,1,2,2,1,-1,-2,-2 };
        const int Kdy[8] = { -2,-2,-1,1,2,2,1,-1 };

        int x = pos.x + Kdx[dir];
        int y = pos.y + Kdy[dir];

        if (0 <= x && x <= 7 && 0 <= y && y <= 7) {
            return { x,y };
        }
        return Epos;
    }
}

namespace HandleMove {
    void CellMoveToPos(Data& data, const Cell& SourceCell, const Position& TargetPos) {
        Cell tempEcell = Ecell;
        tempEcell.pos = SourceCell.pos;
        Cell tempTarget = SourceCell;
        tempTarget.pos = TargetPos;

        data.pushPiece(tempTarget, TargetPos);
        data.pushPiece(tempEcell, SourceCell.pos);
    }

    void SumiCellMoveToPos(Data& data, const Cell& SourceCell, const Position& TargetPos) {
        Cell tempEcell = Ecell;
        tempEcell.pos = SourceCell.pos;
        Cell tempTarget = SourceCell;
        tempTarget.pos = TargetPos;

        data.pushSumiPiece(tempTarget, TargetPos);
        data.pushSumiPiece(tempEcell, SourceCell.pos);
    }
}

namespace calculateMovable{
    enum Sta :uint8_t {
        Straight,//0表示直线
        Diagonal
    };

    void Line(Data& data, const Cell& newCC, const Sta dir)
    {
        const Position newClessPos = newCC.pos;
        const int newClessID = newCC.id;
        Position tempPos = Epos;

        for (int i = dir; i < 8; i += 2) {//dir==0表示直线
            tempPos = newClessPos;
            while (true) {
                tempPos = PosOffset::posMoveNormal(tempPos, i);
                //出界检查
                if (tempPos == Epos)break;

                int temp = data.getPiece(tempPos).id * newClessID;
                if (temp <= 0)data.pushLogicPiece(tempPos, true);
                if (temp != 0) break;//撞到Cell退出
            }
        }
    }

    void King(Data& data, const Cell& newCC)
    {
        Position newClessPos = newCC.pos;
        int newClessID = newCC.id;

        Position tempPos = Epos;
        int camp = (newClessID > 0) ? 1 : -1;
        for (int i = 0; i < 8; i++) {
            tempPos = PosOffset::posMoveNormal(newClessPos, i);
            if (!(tempPos == Epos)) {
                //没有将军检查
                if (data.getPiece(tempPos).id * newClessID <= 0) {
                    data.pushLogicPiece(tempPos, true);
                }
            }
        }
        //王车易位
    }

    void Knight(Data& data, const Cell& newCC)
    {
        Position newClessPos = newCC.pos;
        int newClessID = newCC.id;

        Position tempPos = Epos;
        for (int i = 0; i < 8; i++) {
            tempPos = PosOffset::posMoveKnight(newClessPos, i);//
            if (!(tempPos == Epos)) {
                if (data.getPiece(tempPos).id * newClessID <= 0) {
                    data.pushLogicPiece(tempPos, true);
                }
            }
        }
    }

    void Pawn(Data& data, const Cell& newCC)
    {
        Position newClessPos = newCC.pos;
        int newClessID = newCC.id;

        Position tempPos = Epos;

        //移动
        const int camp = (newClessID > 0) ? 1 : -1;
        tempPos = PosOffset::posMoveNormal(newClessPos, 2 - 2 * camp);
        if (!(tempPos == Epos)) {
            if (data.getPiece(tempPos).id == 0) {
                data.pushLogicPiece(tempPos, true);
                //第二步
                tempPos = PosOffset::posMoveNormal(tempPos, 2 - 2 * camp);
                if (newClessPos.y == (camp == -1 ? 1 : 6) && data.getPiece(tempPos).id == 0) {
                    data.pushLogicPiece(tempPos, true);
                }
            }
        }
        //吃子
        tempPos = PosOffset::posMoveNormal(newClessPos, 6 + camp);//左
        if (!(tempPos == Epos)) {
            if (data.getPiece(tempPos).id * newClessID < 0) {
                data.pushLogicPiece(tempPos, true);
            }
        }
        tempPos = PosOffset::posMoveNormal(newClessPos, 2 - camp);//右
        if (!(tempPos == Epos)) {
            if (data.getPiece(tempPos).id * newClessID < 0) {
                data.pushLogicPiece(tempPos, true);
            }
        }
        //过路兵

        //升变
        /*
        这部分还没写，和时序有关
        */
    }
}

namespace HandleAttack {
    bool isAttackedByLine(Data& data, const Position& pos, const int camp)
    {
        Position tempPos = Epos;
        bool isAttacked = false;

        for (int i = 0; i < 8; i++) {
            tempPos = pos;
            bool isBias = (i % 2 == 1);//斜为真
            while (!(tempPos == Epos)) {
                tempPos = PosOffset::posMoveNormal(tempPos, i);
                int targetID = data.getSumiPiece(tempPos).id;

                if (targetID != 0) {
                    if (targetID * camp == -2) {//后
                        isAttacked = true;
                    }
                    if (isBias) {
                        if (targetID * camp == -3) {//象
                            isAttacked = true;
                        }
                    }
                    else {
                        if (targetID * camp == -5) {//车
                            isAttacked = true;
                        }
                    }
                    break;
                }
            }
        }

        return isAttacked;
    }

    bool isAttackedByKing(Data& data, const Position& pos, const int camp)
    {
        Position tempPos = Epos;
        bool isAttacked = false;

        for (int i = 0; i < 8; i++) {
            tempPos = PosOffset::posMoveNormal(pos, i);
            int targetID = data.getSumiPiece(tempPos).id;
            if (camp * targetID == -1) {//王
                isAttacked = true;
            }
        }

        return isAttacked;
    }

    bool isAttackedByKnight(Data& data, const Position& pos, const int camp)
    {
        Position tempPos = Epos;
        bool isAttacked = false;

        for (int i = 0; i < 8; i++) {
            tempPos = PosOffset::posMoveKnight(pos, i);//
            int targetID = data.getSumiPiece(tempPos).id;
            if (camp * targetID == -4) {//马
                isAttacked = true;
            }
        }

        return isAttacked;
    }

    bool isAttackedByPawn(Data& data, const Position& pos, const int camp)
    {
        const int Move[4] = { 7,1,3,5 };//白左，白右，黑左，黑右

        Position tempPos = Epos;
        bool isAttacked = false;

        int i = (camp == 1 ? 0 : 2);
        int cnt = 0;
        for (i; cnt < 2; cnt++, i++) {
            tempPos = PosOffset::posMoveNormal(pos, Move[i]);
            int targetID = data.getSumiPiece(tempPos).id;
            if (camp * targetID == -6) {//兵
                isAttacked = true;
            }
        }


        return isAttacked;
    }

    bool isAttacked(Data& data, const Position& pos, const int camp)
    {
        return isAttackedByPawn(data, pos, camp) ||
            isAttackedByKnight(data, pos, camp) ||
            isAttackedByKing(data, pos, camp) ||
            isAttackedByLine(data, pos, camp); // 这里内部已经包含车、象、后
    }

    //检查某格是否被攻击
    bool isCellAttackedAtPos(Data& data, const Cell& cell, const Position pos)
    {
        int camp = (cell.id > 0 ? 1 : -1);

        data.initSumiPiece();

        //模拟移动
        HandleMove::SumiCellMoveToPos(data, cell, pos);

        if (cell.id == camp) {//检查是否为王
            return isAttacked(data, pos, camp);
        }
        else {
            const Position& KingPos = data.getKingPos(camp);
            return isAttacked(data, KingPos, camp);
        }
    }

    //检查攻击别人的王
    bool isCellAttackingKing(Data& data, const Cell& cless)
    {
        data.initSumiPiece();

        int camp = (cless.id > 0 ? 1 : -1);
        //const Position& pos = data.getKingPos(-camp);
        //if (isAttacked(data, pos, -camp)) {
            //return true;
        //}
        return false;
    }
}





void Lobby::onEnter(Data& data)
{
    //ctx.renderData.isLobby = true;
}

void Lobby::onExit(Data& data)
{
    
}

void Lobby::tick(Data& data, const IInputLayer::MsgData& out)
{
    //退出
    if (HandleInput::EscPop(data, out))return;

    //开始按钮
    const Position& pos = out.MousePos;
    if (out.isMouseF && HandleInput::Clickbotton(Sarea, pos)) {
        data.gameIntend.pushSelect = true;
    }
}

IGameState::GameSta Lobby::getID() const
{
    return ID;
}

void Select::onEnter(Data& data)
{
    //ctx.renderData.isSelect = true;
}

void Select::onExit(Data& data)
{
    //ctx.renderData.isSelect = false;
}

void Select::tick(Data& data, const IInputLayer::MsgData& out)
{
    //退出
    if (HandleInput::EscPop(data, out))return;

    //单人
    const Position& pos = out.MousePos;
    if (out.isMouseF && HandleInput::Clickbotton(Rarea, pos)) {
        data.gameIntend.pushPuGame = true;
    }
}

IGameState::GameSta Select::getID() const
{
    return ID;
}

void PuGame::onEnter(Data& data)
{
    data.gameIntend.initGameData = true;
}

void PuGame::onExit(Data& data)
{
}

void PuGame::tick(Data& data, const IInputLayer::MsgData& out)
{
    //暂停
    if (HandleInput::EscPuase(data, out))return;

    //鼠标悬浮坐标对应的棋子坐标
    const Position tempSelectingPos = HandleInput::mousePosToPiecePos(out.MousePos);
    data.pushSelectingPos(tempSelectingPos);
    if (out.isMouseF && HandleInput::Clickbotton(Parea, out.MousePos)) {
        handleCellClick(data, tempSelectingPos);

        //printf("(%d,%d)->(%d,%d)\n", data.getSelectingCell(0).pos.x, data.getSelectingCell(0).pos.y, data.getSelectingCell(1).pos.x, data.getSelectingCell(1).pos.y);
    }
}

IGameState::GameSta PuGame::getID() const
{
    return ID;
}

void PuGame::handleCellClick(Data& data, const Position& pos)
{
    //从Source->Target移动
    const Cell& Source = data.getSelectingCell();
    const Cell& Target = data.getPiece(pos);

    if (Source == Ecell) {
        if (Target.id != 0) {
            doSelect(data, pos);          // 点击有棋子 → 选中
            //printf("Cleck\n");
        }
        else {
            doCancel(data);           // 点击空白 → 取消/忽略
            //printf("Exit\n");
        }
        return;   // 结束
    }
    if (Target.id == 0) {
        if (Target == Ecell) {
            doCancel(data);           // 点击空白 → 取消/忽略
            //printf("Exit\n");
        }
        else {
            doCommitMove(data, pos);          // 移动
            //printf("Move\n");
        }
        return;
    }
    if (Target == Source) {
        doCancel(data);
        //printf("Exit\n");
        return;
    }
    if (Source.id * Target.id > 0) {
        doReSelect(data, pos);   // 同阵营 → 切换选中
        //printf("Cleck\n");
    }
    else {
        doCommitMove(data, pos);    // 异阵营 → 攻击/移动
        //printf("Move\n");
    }
}

void PuGame::doSelect(Data& data, const Position& pos)
{
    const Cell& tempCell = data.getPiece(pos);
    data.pushSelectingCell(tempCell);
    //写入合法性棋盘
    data.initLogicPiece();
    calculateMovableArea(data, tempCell);
    calculateAttackedArea(data, tempCell);
}

void PuGame::doReSelect(Data& data, const Position& pos)
{
    data.initSelecting();
    doSelect(data, pos);
}

void PuGame::doCancel(Data& data)
{
    data.initSelecting();
    data.initLogicPiece();
}

void PuGame::doCommitMove(Data& data, const Position& pos)
{
    //从Source->Target移动
    const Cell Source = data.getSelectingCell();
    if (data.getLogicPiece(pos)) HandleMove::CellMoveToPos(data, Source, pos);
    if (Source.id == 1)data.pushKingPos(pos, 1);
    else if (Source.id == -1)data.pushKingPos(pos, -1);
    data.initLogicPiece();
    data.initSelecting();
}

void PuGame::calculateMovableArea(Data& data, const Cell& out)
{
    switch (out.id) {
    case 1:case -1://王
        //移动+吃子
        calculateMovable::King(data, out);

        break;
    case 2:case -2://后
        //移动+吃子
        calculateMovable::Line(data, out, calculateMovable::Sta::Straight);
        calculateMovable::Line(data, out, calculateMovable::Sta::Diagonal);

        break;
    case 3:case -3://象
        //移动+吃子
        calculateMovable::Line(data, out, calculateMovable::Sta::Diagonal);

        break;
    case 4:case -4://马
        //移动+吃子
        calculateMovable::Knight(data, out);

        break;
    case 5:case -5://车
        //移动+吃子
        calculateMovable::Line(data, out, calculateMovable::Sta::Straight);
        //王车易位

        break;
    case 6:case -6://兵
        //移动+吃子
        calculateMovable::Pawn(data, out);

        break;
    default:break;
    }
}

void PuGame::calculateAttackedArea(Data& data, const Cell& out)
{

    //筛选王白给区域
    //if (tempCell.id == 1 || tempCell.id == -1)

    int camp = out.id > 0 ? 1 : -1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            const Position tempPos = { i,j };
            if (data.getLogicPiece(tempPos) && HandleAttack::isCellAttackedAtPos(data, out, tempPos))data.pushLogicPiece(tempPos, false);
        }
    }
}

void Pause::onEnter(Data& data)
{
}

void Pause::onExit(Data& data)
{
}

void Pause::tick(Data& data, const IInputLayer::MsgData& out)
{
    //退出
    if (HandleInput::EscPop(data, out))return;

    
    const Position& pos = out.MousePos;
    //继续游戏
    if (out.isMouseF && HandleInput::Clickbotton(Larea, pos)) {
        data.gameIntend.popSta = true;
    }
    //重新开始
    else if (out.isMouseF && HandleInput::Clickbotton(Marea, pos)) {
        data.gameIntend.rePuGame = true;
    }
    //返回大厅
    else if (out.isMouseF && HandleInput::Clickbotton(Rarea, pos)) {
        data.gameIntend.backLobby = true;
    }
}

IGameState::GameSta Pause::getID() const
{
    return ID;
}
