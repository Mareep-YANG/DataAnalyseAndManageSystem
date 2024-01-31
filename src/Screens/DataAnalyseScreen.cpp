//
// Created by ly on 2024/1/30.
//
#pragma once
#include "../GuiComponents/GuiScreen.cpp"
#include "../GuiComponents/GuiButton.cpp"
#include "graphics.h"
#include <vector>
#include <iostream>
#include "../GuiComponents/GuiInputBox.cpp"
#include "../GuiComponents/GuiControllers.cpp"
// 全局函数
extern void toMainScreen();
extern void launchDataAnalyce();
extern void chooseUp();
extern void chooseDown();
// 全局变量
extern GuiScreen *nowScreen;
extern int nowChooseDataIndex;
extern std::vector<std::string> dataFileNames;
class DataAnalyseScreen : public GuiScreen{
public:
    DataAnalyseScreen() {
        isActive = true;
        initControllers();
    }
    void onUpdate() const override {
        while (isActive) {
            BeginBatchDraw(); // 开始图像批量绘制
            setbkcolor(RGB(250, 250, 250)); // 绘制背景
            cleardevice();
            // 绘制标题栏
            setfillcolor(RGB(243, 238, 240));
            solidrectangle(0, 0, 1024, 60);
            // 绘制分割线
            setfillcolor(RGB(231, 230, 231));
            solidrectangle(0, 60, 1024, 61);
            //绘制标题文字
            settextcolor(BLACK);
            setbkmode(TRANSPARENT);//设置文字背景透明
            settextstyle(40, 0, _T("宋体"), 0, 0, 1000, false, false, false);
            outtextxy(512 - textwidth("数据处理系统") / 2, 30 - textheight("数据处理系统") / 2,
                      _T("数据处理系统"));
            // 绘制信息栏
            setfillcolor(RGB(140, 199, 181));
            solidrectangle(0, 708, 1024, 768);
            // 绘制分割线
            setfillcolor(RGB(231, 230, 231));
            solidrectangle(0, 707, 1024, 708);
            for (GuiControllers *controller: controllersVector) {
                controller->drawController();
            }
            settextcolor(WHITE);
            outtextxy(40, 718, _T("C语言程序设计A课程设计  作者:** 班级:电****"));
            // 绘制文件名
            settextcolor(BLACK);
            settextstyle(30, 0, _T("宋体"), 0, 0, 1000, false, false, false);
            outtextxy(250, 100, _T("请选择要分析的数据文件:"));
            outtextxy(250+(1024-250)/2- textwidth(dataFileNames[nowChooseDataIndex].c_str())/2,200, dataFileNames[nowChooseDataIndex].c_str());
            EndBatchDraw();// 结束图形批量绘制
        }
        nowScreen->onUpdate();
    }
private:
    void initControllers(){
        GuiButton *backButton = new GuiButton(40, 100, 240, 350, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                                     _T("返回主菜单"),toMainScreen);
        controllersVector.push_back(backButton);
        GuiButton *launchButton = new GuiButton(40, 400, 240, 650, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                              _T("启动分析"),launchDataAnalyce);
        controllersVector.push_back(launchButton);
        GuiButton *upButton = new GuiButton(400, 280, 874, 340, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                            _T("下一个"),chooseUp);
        controllersVector.push_back(upButton);
        GuiButton *downButton = new GuiButton(400, 440, 874, 500, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                            _T("上一个"),chooseDown);
        controllersVector.push_back(downButton);
    }
};