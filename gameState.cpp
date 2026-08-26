#include "gameState.h"

//#include <memory>

#include "logicStore.h"
#include "typeRenderData.h"


void Lobby::onEnter(Data& data)
{
    //ctx.renderData.isLobby = true;
}

void Lobby::onExit(Data& data)
{
    
}

void Lobby::tick(Data& data, const IInputLayer::MsgData& out)
{
    const Position& pos = out.MousePos;
    if (out.isMouseF && pos.x >= Sarea.left && pos.x <= Sarea.right && pos.y >= Sarea.top && pos.y <= Sarea.bottom) {
        //¿ªÊ¼
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
}

IGameState::GameSta Select::getID() const
{
    return ID;
}