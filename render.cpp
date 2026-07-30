#include "render.h"

#include "renderBorad.h"

void Renderer::renderPUgame(GameCtx& ctx)
{
}

void Renderer::renderSelect()
{
    //BeginBatchDraw();   // 开始批量绘图（双缓冲）
    //cleardevice();

    // 画后表格
    setlinecolor(RGB(0, 0, 200));
    setlinestyle(PS_SOLID, 3);
    line(310, 240, 770, 240);//上
    line(310, 480, 770, 480);//下
    line(310, 240, 310, 480);//左
    line(770, 240, 770, 480);//右
    setfillcolor(RGB(250, 250, 156));//0Xc0c15e//250, 252, 156
    solidrectangle(312, 242, 768, 478);
    //画左按钮
    setlinecolor(RGB(0, 0, 200));
    setlinecolor(RGB(128, 128, 128));//灰
    setlinestyle(PS_SOLID, 3);
    line(360, 400, 460, 400);
    line(360, 450, 460, 450);
    line(360, 400, 360, 450);
    line(460, 400, 460, 450);
    setfillcolor(RGB(255, 39, 0));//0Xc0c15e//250, 252, 156//50, 200, 200
    setfillcolor(RGB(200, 200, 200));//灰
    solidrectangle(362, 402, 458, 448);
    //画中按钮
    setlinecolor(RGB(0, 0, 200));
    setlinecolor(RGB(128, 128, 128));//灰
    setlinestyle(PS_SOLID, 3);
    line(490, 400, 590, 400);
    line(490, 450, 590, 450);
    line(490, 400, 490, 450);
    line(590, 400, 590, 450);
    setfillcolor(RGB(255, 220, 75));//0Xc0c15e//250, 252, 156
    setfillcolor(RGB(200, 200, 200));//灰
    solidrectangle(492, 402, 588, 448);
    //画右按钮
    setlinecolor(RGB(0, 0, 200));
    setlinestyle(PS_SOLID, 3);
    line(620, 400, 720, 400);
    line(620, 450, 720, 450);
    line(620, 400, 620, 450);
    line(720, 400, 720, 450);
    setfillcolor(RGB(124, 254, 86));//0Xc0c15e//250, 252, 156
    solidrectangle(622, 402, 718, 448);
    //文字
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    settextstyle(16, 0, L"宋体");
    outtextxy(395, 418, L"???");
    outtextxy(525, 418, L"???");
    outtextxy(655, 418, L"双人");
    outtextxy(510, 310, L"选择模式");
    setbkmode(OPAQUE);//TRANSPARENT


    //EndBatchDraw();     // 结束批量绘图，一次性显示所有内容
}

void Renderer::renderLobby()
{
    //BeginBatchDraw();   // 开始批量绘图（双缓冲）
    //cleardevice();

    //画中按钮
    setlinecolor(RGB(0, 0, 200));
    setlinestyle(PS_SOLID, 3);
    line(490, 500, 590, 500);
    line(490, 550, 590, 550);
    line(490, 500, 490, 550);
    line(590, 500, 590, 550);
    setfillcolor(RGB(255, 220, 75));//0Xc0c15e//250, 252, 156
    //setfillcolor(RGB(250, 250, 156));//浅黄
    solidrectangle(492, 502, 588, 548);
    //文字
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    settextstyle(16, 0, L"宋体");
    outtextxy(510, 518, L"开始游戏");
    setbkmode(OPAQUE);//TRANSPARENT


    //EndBatchDraw();     // 结束批量绘图，一次性显示所有内容
}

void Renderer::renderDebug(GameCtx& ctx)
{
    
}

void Renderer::render(RenderState& renderSta)
{
    if (renderSta.isLobby)renderLobby();
}

void Renderer::initEasyX() {
	//生成画布
	initgraph(1080, 720);
	setbkcolor(WHITE);             //设置背景（白）
	cleardevice();

	//字体
	setbkmode(OPAQUE);//TRANSPARENT
}