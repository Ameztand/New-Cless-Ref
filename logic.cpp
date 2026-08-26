#include "logic.h"

#include <memory>

#include "gameState.h"


void Logic::onEnter()
{
	gameSta.initGameSta(ctx);
}

void Logic::tick(const IInputLayer::MsgData& out)
{
	data.pollMsgData(out);
	translateMsg();
	if (intend.isExit)intend.isPause = gameSta.popSta(ctx);
	if (!intend.isPause) {
		//Õ»¶¥
		gameSta.getState()->tick(ctx, out);

		//»»Õ»
		if (intend.replaceSelect) {
			gameSta.pushSta(ctx, std::make_unique<Select>());
			updateSta();
		}
	}

}

void Logic::translateMsg()
{
	const IInputLayer::MsgData& out = data.getMsgData();
	using KeySta = IInputLayer::KeySta;
	
	intend.isExit = (out.Esc == KeySta::falling);

	flag.isDebug = translateDebug();
}

bool Logic::translateDebug()
{
	const IInputLayer::MsgData& out = data.getMsgData();
	using KeySta = IInputLayer::KeySta;

	if (out.F1 == KeySta::falling) {
		flag.isDebug = !flag.isDebug;
		printf("ÇÐ»»\n");
	}
	else if (out.F1 == KeySta::Ldown) {
		flag.LDebug = true;
		printf("3");
	}
	else if (out.F1 == KeySta::rising && flag.LDebug) {
		flag.LDebug = false;
		flag.isDebug = !flag.isDebug;
		printf("4\n");
	}

	return (flag.isDebug || flag.LDebug);
}

bool Logic::Exit()
{
	return gameSta.empty();
}

void Logic::pushRender(StateTable& renderSta)
{
	renderSta = flag;
}

const GameCtx& Logic::pushCtx()
{
	return ctx;
}

void Logic::clearIntend()
{
	intend.clear();
}

void Logic::updateSta()
{
	data.setStaID(gameSta.getStaID());
	data.setStaDepth(gameSta.getStaID());
}
