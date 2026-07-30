#include "gameState.h"

void Lobby::onEnter(GameCtx& ctx)
{
    /*
    data.initKeySta();
    data.initMouseSta();
    data.initIntendPipeLine();
    data.initPieceData();
    data.initPieceData();
    data.initCheckedCless();
    data.setIntendPipeLine_renderLobby(true);
    data.staIDPush(ID);
    */
}

void Lobby::onExit(GameCtx& ctx) {

}

void Lobby::tick(GameCtx& ctx)
{
    /*
    data.setIntendPipeLine_renderLobby(true);

    const Position& pos = data.getMousePos();
    if (data.getMouseSta() == 1 && pos.x >= Sarea.left && pos.x <= Sarea.right && pos.y >= Sarea.top && pos.y <= Sarea.bottom) {
        //¿ªÊ¼
        data.setIntendPipeLine_pushSelect(true);
    }
    */
}

int Lobby::getID() const
{
    return ID;
}