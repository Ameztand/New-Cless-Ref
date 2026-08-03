#pragma once

#include "context.h"

class MsgData;

//========== ×´Ì¬»ù ==========
class IGameState {
public:
    virtual ~IGameState() = default;
    virtual void onEnter(GameCtx& ctx) = 0;
    virtual void onExit(GameCtx& ctx) = 0;
    virtual void tick(GameCtx& ctx, MsgData& msgData) = 0;
    virtual int getID() const = 0;
};