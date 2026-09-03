#include "render.h"

#include "typeRenderData.h"
#include "logicStore.h"
#include "IGameState.h"

namespace renderSelectingRrec {
    enum class ModeSta : uint8_t {
        Select,
        Puase
    };
    enum class LASta : uint8_t {
        line,
        area
    };

    //按钮坐标等数据
    Position bottonCentrePos = { 540,425 };
    int bottonInterval = 130;
    Position bottonSize = { 100,50 };

    //按钮颜色
    constexpr std::array < std::array<COLORREF, 3>, 2 > Select = { {
        { {RGB(128, 128, 128), RGB(128, 128, 128), RGB(50, 130, 250)} },//线
        { {RGB(200, 200, 200), RGB(200, 200, 200), RGB(124, 254, 86)} }//面
        } };
    constexpr std::array < std::array<COLORREF, 3>, 2 > Puase = { {
        { {RGB(100, 204, 106), RGB(80, 180, 180),  RGB(255, 180, 75)} },//线
        { {RGB(124, 254, 86),  RGB(50, 230, 200),  RGB(255, 210, 75)} }//面
        } };
    constexpr std::array<std::array < std::array<COLORREF, 3>, 2 >, 2> renderSelectinRrecColorTable = {
        Select,Puase
    };
    //255, 220, 200肉色
    //0Xc0c15e//250, 252, 156//50, 200, 200
    //setfillcolor(RGB(255, 39, 0));

    //查表(模式，线面，下标)
    COLORREF GetPauseLineColor(const ModeSta& modeSta, const LASta& LASta, const int index) {
        return renderSelectinRrecColorTable[static_cast<uint8_t>(modeSta)][static_cast<uint8_t>(LASta)][index];
    }
}

//===== 辅助函数 =====
void renderRectangle(const renderSelectingRrec::ModeSta modeSta);


    
void Renderer::renderPuGame()
{
    // 格子颜色
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            setfillcolor(colors[((i + j) % 2) ? 1 : 0]);
            solidrectangle(PIECE_START_X + j * PIECE_CELL_SIZE, PIECE_START_Y + i * PIECE_CELL_SIZE, PIECE_START_X + (j + 1) * PIECE_CELL_SIZE, PIECE_START_Y + (i + 1) * PIECE_CELL_SIZE);
        }
    }

    // 网格线
    setlinecolor(BLUE);
    setlinestyle(PS_SOLID, 4);
    for (int i = 0; i <= 8; i++) {
        line(PIECE_START_X, PIECE_START_Y + PIECE_CELL_SIZE * i, PIECE_START_X + PIECE_CELL_SIZE * 8, PIECE_START_Y + PIECE_CELL_SIZE * i);
        line(PIECE_START_X + PIECE_CELL_SIZE * i, PIECE_START_Y, PIECE_START_X + PIECE_CELL_SIZE * i, PIECE_START_Y + PIECE_CELL_SIZE * 8);
    }

    // 坐标文字
    settextcolor(BLACK);
    settextstyle(16, 0, L"宋体");
    setbkmode(TRANSPARENT);
    wchar_t buf[256];
    for (int i = 0; i < 8; i++) {
        //数字
        swprintf(buf, 256, L"%d", 8 - i);
        outtextxy(PIECE_START_X - 20, PIECE_START_Y + i * PIECE_CELL_SIZE + 22, buf);
        //字母
        swprintf(buf, 256, L"%c", L'a' + i);
        outtextxy(PIECE_START_X + i * PIECE_CELL_SIZE + 25, PIECE_START_Y + 8 * PIECE_CELL_SIZE + 10, buf);
    }

    //辅助函数-渲染棋子
    auto renderCell = [&](const Position& pos) {
        const wchar_t* ch = pieceChar[renderData.piece[pos.y][pos.x].id + 6];
        int x = PIECE_START_X + pos.x * PIECE_CELL_SIZE + (PIECE_CELL_SIZE - textwidth(ch)) / 2;
        int y = PIECE_START_Y + pos.y * PIECE_CELL_SIZE + (PIECE_CELL_SIZE - textheight(ch)) / 2;
        outtextxy(x, y, ch);
        };

    // 普通棋子
    Position exCellPos = renderData.selectingCell.pos;
    if (exCellPos == Epos)exCellPos = renderData.selectingPos;
    //printf("%d %d\n", pos.x, pos.y);
    settextstyle(48, 0, L"Segoe UI Symbol");
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Position temp = { i,j };//棋盘[x][y]
            if (temp == exCellPos && renderData.promotion == Ecell)continue;//无升变就正常跳过高亮
            renderCell(temp);
        }
    }

    if (!(renderData.promotion == Ecell))return;//如果升变则跳过高亮和待移动

    //高亮选择
    if (!(exCellPos == Epos)) {
        //高亮棋子
        settextstyle(64, 0, L"Segoe UI Symbol");
        renderCell(exCellPos);
        //高亮边框
        setlinecolor(RGB(255, 255, 0));
        setlinestyle(PS_SOLID, 5);
        rectangle(PIECE_START_X + exCellPos.x * PIECE_CELL_SIZE, PIECE_START_Y + exCellPos.y * PIECE_CELL_SIZE, PIECE_START_X + (exCellPos.x + 1) * PIECE_CELL_SIZE, PIECE_START_Y + (exCellPos.y + 1) * PIECE_CELL_SIZE);
    }

    //待移动格子
    setfillcolor(GREEN);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (renderData.logicPiece[j][i]) {
                int tempDotSize = 5;
                const Position tempPos = { i,j };
                if (tempPos == renderData.selectingPos)tempDotSize = 7;
                solidcircle(PIECE_START_X + PIECE_CELL_SIZE * (i + 0.5), PIECE_START_Y + PIECE_CELL_SIZE * (j + 0.5), tempDotSize);
            }
        }
    }
}

void Renderer::renderGG()
{
    setbkmode(TRANSPARENT);//TRANSPARENT

    settextcolor(BLACK);
    settextstyle(160, 0, L"宋体");
    outtextxy(180, 270, L"GAME OVER");
    settextstyle(16, 0, L"宋体");
 
    //setbkmode(OPAQUE);//TRANSPARENT
}

void Renderer::renderPromotion()
{
    const Cell& tempCell = renderData.promotion;
    if (tempCell == Ecell)return;

    const Position& tempPos = { tempCell.pos.x * 370 / 7 + 10,tempCell.pos.y * PIECE_CELL_SIZE + 8 };//10->380

    // 格子颜色
    for (int i = 0; i < 4; i++) {
        setfillcolor(colors[(i % 2) ? 1 : 0]);
        solidrectangle(tempPos.x + i * PIECE_CELL_SIZE, tempPos.y, tempPos.x + (i + 1) * PIECE_CELL_SIZE, tempPos.y + PIECE_CELL_SIZE);
    }

    // 网格线
    setlinecolor(BLUE);
    setlinestyle(PS_SOLID, 4);
    for (int i = 0; i <= 4; i++) {
        line(tempPos.x, tempPos.y, tempPos.x + PIECE_CELL_SIZE * 4, tempPos.y);
        line(tempPos.x, tempPos.y + PIECE_CELL_SIZE, tempPos.x + PIECE_CELL_SIZE * 4, tempPos.y + PIECE_CELL_SIZE);
        line(tempPos.x + PIECE_CELL_SIZE * i, tempPos.y, tempPos.x + PIECE_CELL_SIZE * i, tempPos.y + PIECE_CELL_SIZE);
    }

    //棋子
    for (int i = 0; i < 4; i++) {
        int camp = tempCell.id > 0 ? 1 : -1;
        const wchar_t* ch = pieceChar[(i + 2) * camp + 6];
        settextstyle(48, 0, L"Segoe UI Symbol");
        if (tempPos.x + PIECE_CELL_SIZE * i < renderData.mosuePos.x && renderData.mosuePos.x < tempPos.x + PIECE_CELL_SIZE * (1 + i) && tempPos.y < renderData.mosuePos.y && renderData.mosuePos.y < tempPos.y + PIECE_CELL_SIZE) {
            settextstyle(64, 0, L"Segoe UI Symbol");
            //高亮边框
            setlinecolor(RGB(255, 255, 0));
            setlinestyle(PS_SOLID, 5);
            rectangle(tempPos.x + PIECE_CELL_SIZE * i, tempPos.y, tempPos.x + PIECE_CELL_SIZE * (1 + i), tempPos.y + PIECE_CELL_SIZE);
        }
        int x = tempPos.x + (PIECE_CELL_SIZE - textwidth(ch)) / 2 + PIECE_CELL_SIZE * i;
        int y = tempPos.y + (PIECE_CELL_SIZE - textheight(ch)) / 2;
        outtextxy(x, y, ch);
    }
}

void Renderer::renderBout()
{
    if (renderData.bout == -1)setfillcolor(BLACK);
    else setfillcolor(WHITE);
    solidrectangle(850, 310, 950, 410);

    setlinecolor(RGB(255, 255, 0));
    setlinestyle(PS_SOLID, 7);
    rectangle(850, 310, 950, 410);


    setbkmode(TRANSPARENT);
    if (renderData.bout == 1) {
        settextstyle(30, 0, L"宋体");
        settextcolor(BLACK);
        outtextxy(870, 346, L"白方");
    }
    else {
        settextstyle(30, 0, L"宋体");
        settextcolor(WHITE);
        outtextxy(870, 346, L"黑方");
    }
    setbkmode(OPAQUE);//TRANSPARENT
}

void Renderer::renderPause()
{
    //背景板
    renderRectangle(renderSelectingRrec::ModeSta::Puase);
    //文字
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
    settextstyle(16, 0, L"宋体");
    outtextxy(380, 418, L"继续游戏");
    outtextxy(510, 418, L"重新开始");
    outtextxy(640, 418, L"返回开始");
    outtextxy(525, 310, L"暂停");
    setbkmode(OPAQUE);//TRANSPARENT
}

void Renderer::renderSelect()
{
    //BeginBatchDraw();   // 开始批量绘图（双缓冲）
    //cleardevice();

    //背景板
    renderRectangle(renderSelectingRrec::ModeSta::Select);
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

void Renderer::renderDebug()
{
    setbkmode(OPAQUE);//TRANSPARENT

    //打印调试
    settextstyle(16, 0, L"宋体");
    wchar_t buf[256];
    swprintf(buf, 256, L"栈深：%d 栈顶ID：%d", renderData.StaDepth, renderData.gameSta);
    outtextxy(10, 10, buf);

    swprintf(buf, 256, L"鼠标坐标：(%d,%d)", renderData.mosuePos.x, renderData.mosuePos.y);
    outtextxy(10, 30, buf);

    Position exCellPos =  renderData.selectingPos;
    int tempID = 0;
    bool tempMovable = false;
    if (!(exCellPos == Epos)) {
        tempID = renderData.piece[exCellPos.y][exCellPos.x].id;
        tempMovable = renderData.logicPiece[exCellPos.y][exCellPos.x];
    }
    swprintf(buf, 256, L"当前鼠标格子： ID:%d   pos:(%d,%d)   LogicPiece:%c", tempID, exCellPos.x, exCellPos.y, tempMovable ? L'T' : L'F');
    outtextxy(10, 50, buf);
    exCellPos = renderData.selectingCell.pos;
    swprintf(buf, 256, L"当前持有格子： ID:%d   pos:(%d,%d)", renderData.selectingCell.id, exCellPos.x, exCellPos.y);
    outtextxy(10, 70, buf);

    swprintf(buf, 256, L"王的位置： Wpos:(%d , %d)   Bpos:(%d , %d)", renderData.KingPos[0].x, renderData.KingPos[0].y, renderData.KingPos[1].x, renderData.KingPos[1].y);
    outtextxy(10, 90, buf);

    swprintf(buf, 256, L"过路兵坐标:（%d,%d）    是否允许移位WB: %d%d", renderData.passedPawn.pos.x, renderData.passedPawn.pos.y, renderData.KingChecked.id, renderData.checkmate);
    outtextxy(10, 110, buf);

    swprintf(buf, 256, L"被将军的王： %d    被将死的王： %d", renderData.KingChecked.id, renderData.checkmate);
    outtextxy(10, 130, buf);


    setbkmode(TRANSPARENT);//TRANSPARENT
}

void Renderer::render(const RenderData& out)
{
    if (out.gameSta != renderData.gameSta)prveGameSta = renderData.gameSta;
    renderData = out;

    BeginBatchDraw();   // 开始批量绘图（双缓冲）
    cleardevice();

    //栈式结构
    using GameSta = IGameState::GameSta;
    switch (out.gameSta) {
    case GameSta::Lobby:
        renderLobby();
        break;
    case GameSta::Select:
        renderSelect();
        break;
    case GameSta::Pause:
        //背景板
        renderBout();
        switch (prveGameSta) {
        case GameSta::PuGame:
            renderPuGame();
            break;
        }

        renderPromotion();
        if (out.checkmate != 0)renderGG();
        renderPause();

        break;
    case GameSta::PuGame:
        renderBout();
        renderPuGame();
        renderPromotion();
        if (out.checkmate != 0)renderGG();

        break;
    }

    
    if (out.isDebug)renderDebug();

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

void renderRectangle(const renderSelectingRrec::ModeSta modeSta)
{
    using LA = renderSelectingRrec::LASta;

    // 画按钮
    auto renderBotton = [&](const renderSelectingRrec::ModeSta modeSta, int index) {
        setlinecolor(renderSelectingRrec::GetPauseLineColor(modeSta, LA::line, index));//灰
        setlinestyle(PS_SOLID, 3);
        int left   = renderSelectingRrec::bottonCentrePos.x - renderSelectingRrec::bottonSize.x / 2 + renderSelectingRrec::bottonInterval * (index - 1);
        int top    = renderSelectingRrec::bottonCentrePos.y - renderSelectingRrec::bottonSize.y / 2;
        int right  = renderSelectingRrec::bottonCentrePos.x + renderSelectingRrec::bottonSize.x / 2 + renderSelectingRrec::bottonInterval * (index - 1);
        int bottom = renderSelectingRrec::bottonCentrePos.y + renderSelectingRrec::bottonSize.y / 2;
        rectangle(left, top, right, bottom);
        setfillcolor(renderSelectingRrec::GetPauseLineColor(modeSta, LA::area, index));//灰
        solidrectangle(left + 2, top + 2, right - 2, bottom - 2);
        };

    // 画后表格
    setlinecolor(RGB(50, 150, 250));
    setlinestyle(PS_SOLID, 6);
    rectangle(310, 240, 770, 480);
    setfillcolor(RGB(250, 250, 156));//0Xc0c15e//250, 252, 156
    solidrectangle(312, 242, 768, 478);
    
    // 画按钮
    for (int i = 0; i < 3; i++) {
        renderBotton(modeSta, i);
    }
}
