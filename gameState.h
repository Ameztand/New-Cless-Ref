#pragma once

#include "IGameState.h"
#include "common.h"

//大厅
class Lobby :public IGameState {
private:
    const int ID = STA_LOBBY;

public:
    void onEnter(GameCtx& ctx)override;
    void onExit(GameCtx& ctx) override;
    void tick(GameCtx& ctx, MsgData& msgData)override;
    int getID() const override;
};

//选择难度
class Select :public IGameState {
private:
    const int ID = STA_SELECT;

public:
    void onEnter(GameCtx& ctx)override;
    void onExit(GameCtx& ctx) override;
    void tick(GameCtx& ctx, MsgData& msgData)override;
    int getID() const override;
};
