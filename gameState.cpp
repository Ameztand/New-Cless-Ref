#include "gameState.h"

//#include <memory>

#include "logicStore.h"
#include "typeRenderData.h"

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
    if (EscPop(data, out))return;

    //开始按钮
    const Position& pos = out.MousePos;
    if (out.isMouseF && pos.x >= Sarea.left && pos.x <= Sarea.right && pos.y >= Sarea.top && pos.y <= Sarea.bottom) {
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
    if (EscPop(data, out))return;

    //单人
    const Position& pos = out.MousePos;
    if (out.isMouseF && pos.x >= Rarea.left && pos.x <= Rarea.right && pos.y >= Rarea.top && pos.y <= Rarea.bottom) {
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
    if (EscPuase(data, out))return;

    
}

IGameState::GameSta PuGame::getID() const
{
    return ID;
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
    if (EscPop(data, out))return;

    //退出
    const Position& pos = out.MousePos;
    if (out.isMouseF && pos.x >= Rarea.left && pos.x <= Rarea.right && pos.y >= Rarea.top && pos.y <= Rarea.bottom) {
        data.gameIntend.backLobby = true;
    }
    //继续
    else if (out.isMouseF && pos.x >= Larea.left && pos.x <= Larea.right && pos.y >= Larea.top && pos.y <= Larea.bottom) {
        data.gameIntend.popSta = true;
    }
    //重开
    else if (out.isMouseF && pos.x >= Marea.left && pos.x <= Marea.right && pos.y >= Marea.top && pos.y <= Marea.bottom) {
        data.gameIntend.rePuGame = true;
    }
}

IGameState::GameSta Pause::getID() const
{
    return ID;
}
