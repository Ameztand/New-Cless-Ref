#pragma once

#include "IGameState.h"
#include "common.h"

//´óÌü
class Lobby :public IGameState {
private:
    const int ID = STA_LOBBY;

public:
    void onEnter(GameCtx& ctx)override;
    void onExit(GameCtx& ctx) override;
    void tick(GameCtx& ctx)override;
    int getID() const override;
};
