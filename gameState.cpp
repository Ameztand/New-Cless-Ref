#include "gameState.h"

//#include <memory>

#include "msgBoard.h"
#include "gameBoard.h"
#include "StateTable.h"


void Lobby::onEnter(GameCtx& ctx)
{
    ctx.flag.isLobby = true;
}

void Lobby::onExit(GameCtx& ctx)
{
    
}

void Lobby::tick(GameCtx& ctx, MsgData& msgData)
{
    const Position& pos = msgData.getMousePos();
    if (msgData.getMouseF() && pos.x >= Sarea.left && pos.x <= Sarea.right && pos.y >= Sarea.top && pos.y <= Sarea.bottom) {
        //¿ªÊ¼
        ctx.intend.replaceSelect = true;
    }
}

int Lobby::getID() const
{
    return ID;
}

void Select::onEnter(GameCtx& ctx)
{
    ctx.flag.isSelect = true;
}

void Select::onExit(GameCtx& ctx)
{
    ctx.flag.isSelect = false;
}

void Select::tick(GameCtx& ctx, MsgData& msgData)
{
}

int Select::getID() const
{
    return ID;
}