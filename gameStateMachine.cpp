#include "gameStateMachine.h"

#include "gameState.h"

void State::pushSta(GameCtx& ctx, std::unique_ptr<IGameState> newState) {
    if (newState) {
        newState->onEnter(ctx);           // 自动调用具体状态的 onEnter
        stack.push(std::move(newState));
    }
}

void State::popSta(GameCtx& ctx) {
    if (!stack.empty()) {
        stack.top()->onExit(ctx);          // 自动调用具体状态的 onExit
        stack.pop();
    }
}

void State::changeSta(GameCtx& ctx, std::unique_ptr<IGameState> newState) {
    if (!stack.empty()) {
        stack.top()->onExit(ctx);          // 自动调用具体状态的 onExit
        stack.pop();
    }
    if (newState) {
        newState->onEnter(ctx);           // 自动调用具体状态的 onEnter
        stack.push(std::move(newState));
    }
}

//获取栈顶对象
IGameState* State::getState() {
    return stack.empty() ? nullptr : stack.top().get();
}

bool State::empty() {
    return stack.empty();
}

int State::getStaDepth() const {
    return (int)stack.size();
}

int State::getStaID()const {
    return (stack.empty()) ? 0 : stack.top()->getID();
}

void State::initGameSta(GameCtx& ctx)
{
    while (!stack.empty()) {
        stack.pop();
    }
    pushSta(ctx, std::make_unique<Lobby>());
}
