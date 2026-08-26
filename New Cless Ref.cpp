#include <iostream>

#include <easyx.h>

#include "inputLayer.h"
#include "render.h"
#include "logic.h"


#pragma comment(lib, "winmm.lib")   //提高定时器精度



int main()
{
	timeBeginPeriod(1);  // // 提高定时器精度,全局设置，程序结束时记得 timeEndPeriod(1)

	InputLayer inputLayer;

	Renderer render;

	Logic logic;

	inputLayer.initInputLayer();
	logic.onEnter();
	render.initEasyX();

	while (true) {
		if (logic.Exit())break;

		inputLayer.poll();
		logic.tick(inputLayer.getMsgData());

		render.render(logic.pushRender());

		logic.clearIntend();

		Sleep(10);
	}


	timeEndPeriod(1);
	closegraph();
	return 0;
}