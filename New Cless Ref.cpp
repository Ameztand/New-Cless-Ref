#include <iostream>

#include <easyx.h>

#include "logic.h"
#include "sysCommand.h"

#pragma comment(lib, "winmm.lib")   //提高定时器精度

int main()
{
	timeBeginPeriod(1);  // // 提高定时器精度,全局设置，程序结束时记得 timeEndPeriod(1)

	Logic logic;
	SysCommand sysCommand;

	logic.onEnter();


	//生成画布
	initgraph(1080, 720);
	setbkcolor(WHITE);             //设置背景（白）
	cleardevice();

	//字体
	setbkmode(OPAQUE);//TRANSPARENT

	while (true) {
		if (sysCommand.getExit())break;
		sysCommand.clear();

		logic.tick(sysCommand);

		
		Sleep(10);
	}


	timeEndPeriod(1);
	closegraph();
	return 0;
}