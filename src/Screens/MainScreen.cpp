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
extern void toDataAnalyseSystem();
extern void logOutProcessor();
extern void toManageScreen();
// 全局变量
extern GuiScreen *nowScreen;
class MainScreen : public GuiScreen{
public:
    MainScreen() {
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
            outtextxy(512 - textwidth("数据处理与信息管理系统") / 2, 30 - textheight("数据处理与信息管理系统") / 2,
                      _T("数据处理与信息管理系统"));
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
            EndBatchDraw();// 结束图形批量绘制
        }
        nowScreen->onUpdate();
    }
private:
    void initControllers(){
        GuiButton *dataAnalyseButton = new GuiButton(80, 200, 944, 260, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                              _T("数据分析系统"),toDataAnalyseSystem);
        controllersVector.push_back(dataAnalyseButton);
        GuiButton *dataManageButton = new GuiButton(80, 360, 944, 420, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                                    _T("数据管理系统"),toManageScreen);
        controllersVector.push_back(dataManageButton);
        GuiButton *logOutButton = new GuiButton(80, 520, 944, 580, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                                    _T("退出登录"),logOutProcessor);
        controllersVector.push_back(logOutButton);
    }
};