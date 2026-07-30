#pragma once

#include <memory>
#include <stack>

//#include "common.h"
#include "IGameState.h"



// ========== 状态机管理器 ==========
class State {
private:
    std::stack<std::unique_ptr<IGameState>> stack;

public:
    // 压栈
    void pushSta(GameCtx& ctx, std::unique_ptr<IGameState> newState);

    //弹出
    void popSta(GameCtx& ctx);

    //替换
    void changeSta(GameCtx& ctx, std::unique_ptr<IGameState> newState);

    //获取栈顶对象
    IGameState* getState();

    //是否为空
    bool empty();

    // 获取栈深度
    int getStaDepth() const;

    //获取栈顶id
    int getStaID()const;

    //初始化
    void initGameSta(GameCtx& ctx);
};