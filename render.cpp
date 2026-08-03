#include "render.h"

#include "StateTable.h"
#include "gameBoard.h"

void Renderer::renderPUgame(const GameCtx& ctx)
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

void Renderer::renderDebug(const GameCtx& ctx)
{
    setbkmode(OPAQUE);//TRANSPARENT

    //打印调试
    settextstyle(16, 0, L"宋体");
    wchar_t buf[256];
    swprintf(buf, 256, L"栈深：%d 栈顶ID：%d", ctx.data.getStaDepth(), ctx.data.getStaID());
    outtextxy(10, 10, buf);
    /*
    const Position& tempPos1 = data.getMousePos();
    const Position& tempPos2 = data.getPiecePos();
    swprintf(buf, 256, L"鼠标坐标：(%d , %d)", tempPos1.x, tempPos1.y);
    outtextxy(10, 30, buf);
    const Cell& tempCell = data.getOnePieceData(tempPos2);
    const bool& tempBool = data.getOneLogicPiece(tempPos2);
    swprintf(buf, 256, L"鼠标当前格子： ID:%d   pos:(%d , %d)   hasMoved:%d   LogicPiece:%d", tempCell.id, tempCell.pos.x, tempCell.pos.y, tempCell.hasMoved, tempBool);
    outtextxy(10, 50, buf);
    const Cell& tempCell2 = data.getCheckedCless()[0];
    swprintf(buf, 256, L"持有棋子： ID:%d   pos:(%d , %d)   hasMoved:%d", tempCell2.id, tempCell2.pos.x, tempCell2.pos.y, tempCell2.hasMoved);
    outtextxy(10, 70, buf);
    const Position& tempPos3 = data.getKingPos(1);
    const Position& tempPos4 = data.getKingPos(-1);
    swprintf(buf, 256, L"王的位置： Wpos:(%d , %d)   Bpos:(%d , %d)", tempPos3.x, tempPos3.y, tempPos4.x, tempPos4.y);
    outtextxy(10, 90, buf);
    const bool& tempBool2 = data.getKingChecked(1);
    const bool& tempBool3 = data.getKingChecked(-1);
    swprintf(buf, 256, L"王的被将军状态： Wpos:%d   Bpos:%d", tempBool2, tempBool3);
    outtextxy(10, 110, buf);
    */

    setbkmode(TRANSPARENT);//TRANSPARENT
}

void Renderer::render(const StateTable& renderSta, const GameCtx& ctx)
{
    BeginBatchDraw();   // 开始批量绘图（双缓冲）
    cleardevice();

    //栈式结构
    if (renderSta.isSelect)renderSelect();
    else if (renderSta.isLobby)renderLobby();

    if (renderSta.isDebug)renderDebug(ctx);

    EndBatchDraw();     // 结束批量绘图，一次性显示所有内容
}

void Renderer::initEasyX() {
	//生成画布
	initgraph(1080, 720);
	setbkcolor(WHITE);             //设置背景（白）
	cleardevice();

	//字体
	setbkmode(OPAQUE);//TRANSPARENT
}