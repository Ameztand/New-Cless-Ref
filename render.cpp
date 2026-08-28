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
            if (temp == exCellPos)continue;
            renderCell(temp);
        }
    }

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

    /*
    //待移动格子
    const LogicPiece& tempLogicPiece = data.getAllLogicPiece();
    setfillcolor(GREEN);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (tempLogicPiece[j][i]) {
                solidcircle(PIECE_START_X + PIECE_CELL_SIZE * (i + 0.5), PIECE_START_Y + PIECE_CELL_SIZE * (j + 0.5), 5);
            }
        }
    }
    */
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

    swprintf(buf, 256, L"鼠标坐标：(%4d , %4d)", renderData.mosuePos.x, renderData.mosuePos.y);
    outtextxy(10, 30, buf);
    /*
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
        switch (prveGameSta) {
        case GameSta::PuGame:
            renderPuGame();
            break;
        }

        renderPause();
        break;
    case GameSta::PuGame:
        renderPuGame();
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
