#pragma once

//#include <cstdint>//£¿
#include "IInputLayer.h"
//#include "logicStore.h"

class Data;

//========== ×´Ì¬»ù ==========
class IGameState {
public:
    enum class GameSta :uint8_t {
        null,
        Lobby,
        Select,
        game,
        pause
    };

    virtual ~IGameState() = default;
    virtual void onEnter(Data& data) = 0;
    virtual void onExit(Data& data) = 0;
    virtual void tick(Data& data, const IInputLayer::MsgData& out) = 0;
    virtual IGameState::GameSta getID() const = 0;
};