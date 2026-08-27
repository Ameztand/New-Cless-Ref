#pragma once


#include "common.h"

#include "logicStore.h"
#include "gameStateMachine.h"

#include "typeRenderData.h"

#include"IInputLayer.h"


class Logic {
private:
	Data data;
	State gameSta;

	//引用本体
	RenderData tempRenderData;
public:
	void onEnter();

	void tick(const IInputLayer::MsgData& out);

	void translateMsg();

	void translateDebug();

	//检查ESC退出
	bool Exit();

	//返回渲染数据
	const RenderData& pushRender();

	//清理意图管线
	void clearIntend();
};
