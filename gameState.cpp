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
                    if (targetID * camp == -2) isAttacked = true;//后
                    if (isBias) {
                        if (targetID * camp == -3) isAttacked = true;//象
                    }
                    else {
                        if (targetID * camp == -5) isAttacked = true;//车
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

    //检查pos是否被攻击(在pos被攻击的cell的camp)
    bool isAttackedInPos(Data& data, const Position& pos, const int camp)
    {
        return isAttackedByPawn(data, pos, camp) ||
            isAttackedByKnight(data, pos, camp) ||
            isAttackedByKing(data, pos, camp) ||
            isAttackedByLine(data, pos, camp); // 这里内部已经包含车、象、后
    }

    //检查cell移动到pos后王是否被攻击
    bool isCheckedWhenCellToPos(Data& data, const Cell& cell, const Position pos)
    {
        int camp = (cell.id > 0 ? 1 : -1);

        data.initSumiPiece();

        //模拟移动
        HandleMove::SumiCellMoveToPos(data, cell, pos);

        if (cell.id == camp) {//检查是否为王
            return isAttackedInPos(data, pos, camp);
        }
        else {
            const Position& KingPos = data.getKingPos(camp);
            return isAttackedInPos(data, KingPos, camp);
        }
    }

    //检查别人的王是否被攻击（返回被攻击的王）
    const Cell& isCellAttackKing(Data& data, const Cell& cell)
    {
        data.initSumiPiece();

        int camp = (cell.id > 0 ? 1 : -1);
        const Position& pos = data.getKingPos(-camp);
        if (isAttackedInPos(data, pos, -camp)) {
            return data.getPiece(pos);
        }
        return Ecell;
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
        const Position KingPos= data.getKingPos(camp);
        

        auto caslting = [&](Data& data, int i) {
            if (!data.getCanCastling(camp))return;
            int dir[2] = { 6,2 };
            Position pos = KingPos;
            while (true) {
                pos = PosOffset::posMoveNormal(pos, dir[i]);//方向
                //printf("检查(%d,%d)\n", pos.x, pos.y);
                if (pos == Epos)break;
                if (data.getPiece(pos).id * camp == 5) {//id为车
                    //王车易位
                    const Position tempPos2 = { KingPos.x + i * 4 - 2,KingPos.y };
                    //printf("发现(%d,%d)可以移位\n", tempPos2.x, tempPos2.y);
                    data.pushLogicPiece(tempPos2, true);
                }
                else {
                    if (data.getPiece(pos).id != 0 || HandleAttack::isAttackedInPos(data, pos, camp))break;//被攻击或者非空就退出
                }
            }
        };

        caslting(data, 0);//左
        caslting(data, 1);//右
        
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
        auto attack = [&](int i) {
            int dir[2] = { 6 + camp ,2 - camp };
            tempPos = PosOffset::posMoveNormal(newClessPos, dir[i]);
            if (!(tempPos == Epos)) {
                if (data.getPiece(tempPos).id * newClessID < 0) {
                    data.pushLogicPiece(tempPos, true);
                }
            }
        };
        attack(0);//左
        attack(1);//右
        
        //过路兵
        if (newClessPos.y - camp == data.getPassedPawn().pos.y) {
            if (newClessPos.x + 1 == data.getPassedPawn().pos.x) {
                tempPos = newClessPos;
                tempPos = PosOffset::posMoveNormal(tempPos, 2 - camp);//1-3
                data.pushLogicPiece(tempPos, true);
            }
            if (newClessPos.x - 1 == data.getPassedPawn().pos.x) {
                tempPos = newClessPos;
                tempPos = PosOffset::posMoveNormal(tempPos, 6 + camp);//7-5
                data.pushLogicPiece(tempPos, true);
            }
        }

        //升变
        /*
        这部分还没写，和时序有关
        */
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
    if (data.getPromotion() == Ecell) {
        //普通
        if (out.isMouseF && HandleInput::Clickbotton(Parea, out.MousePos) && data.getCheckmate() == 0) {
            handleCellClick(data, tempSelectingPos);
        }
    }
    else {
        //升变
        handlePromotion(data, out);
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

void PuGame::handlePromotion(Data& data, const IInputLayer::MsgData& out)
{
    //升变选择
    const Cell tempCell = data.getPromotion();
    const Position tempPos = { tempCell.pos.x * 370 / 7 + 10,tempCell.pos.y * PIECE_CELL_SIZE + 8 };//10->380
    for (int i = 0; i < 4; i++) {
        //升变选择区域（抄render的）
        RECT tempArea = { tempPos.x + PIECE_CELL_SIZE * i, tempPos.y, tempPos.x + PIECE_CELL_SIZE * (1 + i), tempPos.y + PIECE_CELL_SIZE };
        //检查点击
        if (out.isMouseF && HandleInput::Clickbotton(tempArea, out.MousePos)) {
            Cell tempCellpro = Ecell;
            tempCellpro.pos = tempCell.pos;
            tempCellpro.id = tempCell.id > 0 ? 2 + i : -2 - i;
            data.pushPiece(tempCellpro, tempCellpro.pos);
            data.initPromotion();

            //屎山生成ing//又莫名其妙的好了为什么？
            //data.pushSelectingCell(tempCellpro);
            //doCommitMove(data, tempCellpro.pos);

            examCheck(data, data.getPiece(tempCellpro.pos));
            examCheckmate(data, tempCellpro.id > 0 ? -1 : 1);//选择对面阵营
            data.initLogicPiece();
        }
    }
}

void PuGame::doSelect(Data& data, const Position& pos)
{
    const Cell& tempCell = data.getPiece(pos);
    if (tempCell.id * data.getBout() <= 0)return;

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
    const Cell Source = data.getSelectingCell();
    const int camp = Source.id > 0 ? 1 : -1;

    //从Source->Target移动(传参pos就是Target)
    bool move = false;
    if (data.getLogicPiece(pos)) {
        HandleMove::CellMoveToPos(data, Source, pos);
        move = true;
    }
    if (Source.id == camp)data.pushKingPos(pos, camp);

    if (move) {
        //王车易位车移动
        const Position& newKingPos = data.getKingPos(camp);
        if (data.getCanCastling(camp)) {
            int dir[2] = { 7,0 };//白黑
            int i = (camp == 1) ? dir[0] : dir[1];

            //printf("(%d,%d)\n", newKingPos.x, newKingPos.y);
            if (newKingPos.x == 2) HandleMove::CellMoveToPos(data, data.getPiece({ 0,i }), { 3,i });
            else if (newKingPos.x == 6) HandleMove::CellMoveToPos(data, data.getPiece({ 7,i }), { 5,i });
        }
        //消除王车易位标识符
        if (Source.id == camp || Source.id == 5 * camp) data.pushCanCastling(false, camp);

        //过路兵标识-add
        if (Source.id == 6 && Source.pos.y == 6 && pos.y == 4) {
            Cell tempPPCell = Source;
            tempPPCell.pos.y = 5;
            data.pushPassedPawn(tempPPCell);
            printf("添加（%d,%d）\n", tempPPCell.pos.x, tempPPCell.pos.y);
        }
        else if (Source.id == -6 && Source.pos.y == 1 && pos.y == 3) {
            Cell tempPPCell = Source;
            tempPPCell.pos.y = 2;
            data.pushPassedPawn(tempPPCell);
            printf("添加（%d,%d）\n", tempPPCell.pos.x, tempPPCell.pos.y);
        }
        else {
            //过路兵标识-remove
            if (Source.id == 6 && pos == data.getPassedPawn().pos) {
                Cell tempPPCell = data.getPassedPawn();
                tempPPCell.pos.y++;
                tempPPCell.id = 0;
                data.pushPiece(tempPPCell, tempPPCell.pos);
                //printf("清理（%d,%d）\n", tempPPCell.pos.x, tempPPCell.pos.y);
            }
            else if (Source.id == -6 && pos == data.getPassedPawn().pos) {
                Cell tempPPCell = data.getPassedPawn();
                tempPPCell.pos.y--;
                tempPPCell.id = 0;
                data.pushPiece(tempPPCell, tempPPCell.pos);
                //printf("清理（%d,%d）\n", tempPPCell.pos.x, tempPPCell.pos.y);
            }
            else {
                //printf("默认清理\n");
            }

            data.initPassedPawn();
        }

        //小兵升变
        if ((Source.id == 6 && pos.y == 0) || (Source.id == -6 && pos.y == 7)) {
            data.pushPromotion(data.getPiece(pos));
        }
        else {
            data.initPromotion();//临时
        }



        //要调整到tick？
        examCheck(data, data.getPiece(pos));
        examCheckmate(data, Source.id > 0 ? -1 : 1);//选择对面阵营

        //清理
        data.initLogicPiece();
        data.initSelecting();

        //更新回合
        data.updataBout();
    }
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
    int camp = out.id > 0 ? 1 : -1;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            const Position tempPos = { i,j };
            if (data.getLogicPiece(tempPos) && HandleAttack::isCheckedWhenCellToPos(data, out, tempPos))data.pushLogicPiece(tempPos, false);
        }
    }
}

void PuGame::examCheck(Data& data, const Cell& cell)
{
    const Cell& tempKingCell = HandleAttack::isCellAttackKing(data, cell);
    if (tempKingCell == Ecell) {
        int camp = cell.id > 0 ? 1 : -1;
        const Position& KingPos = data.getKingPos(-camp);//对面的王
        if (HandleAttack::isAttackedInPos(data, KingPos, -camp)) {//对面的王
            //受到间接攻击
            data.pushKingChecked(data.getPiece(KingPos));
        }
        else {
            //没有收到攻击
            data.initKingChecked();
        }
    }
    else {
        //直接将军
        data.pushKingChecked(tempKingCell);
    }
}

void PuGame::examCheckmate(Data& data, const int camp)
{

    bool hasSolut = false;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            const Position tempPos = { i,j };
            const Cell& tempCell = data.getPiece(tempPos);
            if (tempCell.id * camp > 0) {
                data.initLogicPiece();
                calculateMovableArea(data, tempCell);
                calculateAttackedArea(data, tempCell);//已经筛选了白给和垫将

                //遍历是否存在可移动位置
                for (int ii = 0; ii < 8; ii++) {
                    for (int jj = 0; jj < 8; jj++) {
                        const Position tempPos2 = { ii,jj };
                        hasSolut = data.getLogicPiece(tempPos2);
                        if (hasSolut)break;
                    }
                    if (hasSolut)break;
                }
            }
            if (hasSolut)break;
        }
        if (hasSolut)break;
    }

    if (!hasSolut) {
        if (data.getKingChecked().id != 0) {
            printf("无解\n");
            data.pushCheckmate(camp);
        }
        else {
            printf("和棋\n");
            data.initCheckmate();
        }
    }
    else {
        //没将死
        data.initCheckmate();
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
