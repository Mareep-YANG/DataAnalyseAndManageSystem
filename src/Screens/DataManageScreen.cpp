//
// Created by ly on 2024/1/31.
//
#pragma once
#include "../GuiComponents/GuiScreen.cpp"
#include "../GuiComponents/GuiButton.cpp"
#include "graphics.h"
#include <vector>
#include <iostream>
#include "../GuiComponents/GuiInputBox.cpp"
#include "../GuiComponents/GuiControllers.cpp"
#include "../Entities/SavedDataEntity.cpp"
// 全局函数
extern void toMainScreen();
extern void chooseUpManage();
extern void chooseDownManage();
extern void deleteDataProcessor();
extern void viewData();
// 全局变量
extern GuiScreen *nowScreen;
extern std::vector<SavedDataEntity> savedDatas;
extern int nowChooseSavedDataIndex;
extern bool  ifViewData ;
class DataManageScreen : public GuiScreen{
public:
    DataManageScreen() {
        ifViewData = false;
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
            outtextxy(512 - textwidth("信息管理系统") / 2, 30 - textheight("信息管理系统") / 2,
                      _T("信息管理系统"));
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
            settextcolor(BLACK);
            settextstyle(40, 0, _T("宋体"), 0, 0, 1000, false, false, false);
            outtextxy(40,400,"当前存储的数据数:");
            outtextxy(180,480,std::to_string(savedDatas.size()).c_str());
            outtextxy(500,400,"当前选中的数据文件名");
            if (!savedDatas.empty()){
                outtextxy(640,480,savedDatas[nowChooseSavedDataIndex].filename.c_str());
            }
            if (ifViewData&&!savedDatas.empty()){
                settextstyle(30, 0, _T("宋体"), 0, 0, 1000, false, false, false);
                outtextxy(40,560,("最优阶数:"+std::to_string(savedDatas[nowChooseSavedDataIndex].optiOrder)).c_str());
                outtextxy(40,590,("最优阶数的拟合误差均值:"+std::to_string(savedDatas[nowChooseSavedDataIndex].meanOfOptiOrder)).c_str());
                outtextxy(40,620,("最优阶数的拟合误差方差:"+std::to_string(savedDatas[nowChooseSavedDataIndex].varianceOfOptiOrder)).c_str());
            }
            EndBatchDraw();// 结束图形批量绘制
        }
        nowScreen->onUpdate();
    }
private:
    void initControllers(){
        GuiButton *backButton = new GuiButton(40, 100, 240, 350, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                              _T("返回主菜单"),toMainScreen);
        controllersVector.push_back(backButton);
        GuiButton *deleteDataButton = new GuiButton(260, 100, 460, 350, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                                _T("删除该数据"),deleteDataProcessor);
        controllersVector.push_back(deleteDataButton);
        GuiButton *viewDataButton = new GuiButton(480, 100, 680, 350, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                                    _T("查看数据"),viewData);
        controllersVector.push_back(viewDataButton);
        GuiButton *upButton = new GuiButton(700, 100, 984, 160, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                            _T("下一个"),chooseUpManage);
        controllersVector.push_back(upButton);
        GuiButton *downButton = new GuiButton(700, 290, 984, 350, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                              _T("上一个"),chooseDownManage);
        controllersVector.push_back(downButton);
    }
};