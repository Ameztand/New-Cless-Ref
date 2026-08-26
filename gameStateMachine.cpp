#include "gameStateMachine.h"

#include "gameState.h"

void State::pushSta(Data& data, std::unique_ptr<IGameState> newState) {
    if (newState) {
        newState->onEnter(data);           // 自动调用具体状态的 onEnter
        stack.push(std::move(newState));
    }
}

bool State::popSta(Data& data) {
    if (stack.empty()) {
        return true;
    }

    stack.top()->onExit(data);          // 自动调用具体状态的 onExit
    stack.pop();

    return stack.empty();
}

void State::changeSta(Data& data, std::unique_ptr<IGameState> newState) {
    if (!stack.empty()) {
        stack.top()->onExit(data);          // 自动调用具体状态的 onExit
        stack.pop();
    }
    if (newState) {
        newState->onEnter(data);           // 自动调用具体状态的 onEnter
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

IGameState::GameSta State::getStaID()const {
    return (stack.empty()) ? IGameState::GameSta::null : stack.top()->getID();
}

void State::initGameSta(Data& data)
{
    while (!stack.empty()) {
        stack.pop();
    }
    pushSta(data, std::make_unique<Lobby>());
}
