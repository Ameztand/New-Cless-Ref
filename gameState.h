#pragma once

#include "IGameState.h"
#include "common.h"

//大厅
class Lobby :public IGameState {
private:
    const IGameState::GameSta ID= IGameState::GameSta::Lobby;

public:
    void onEnter(Data& data)override;
    void onExit(Data& data) override;
    void tick(Data& data, const IInputLayer::MsgData& out)override;
    IGameState::GameSta getID() const override;
};

//选择难度
class Select :public IGameState {
private:
    const IGameState::GameSta ID = IGameState::GameSta::Select;

public:
    void onEnter(Data& data)override;
    void onExit(Data& data) override;
    void tick(Data& data, const IInputLayer::MsgData& out)override;
    IGameState::GameSta getID() const override;
};
