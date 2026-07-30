#pragma once

#include "context.h"

//========== ×´Ì¬»ù ==========
class IGameState {
public:
    virtual ~IGameState() = default;
    virtual void onEnter(GameCtx& ctx) = 0;
    virtual void onExit(GameCtx& ctx) = 0;
    virtual void tick(GameCtx& ctx) = 0;
    virtual int getID() const = 0;
};