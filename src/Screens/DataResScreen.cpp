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
#include "../GuiComponents/GuiLabel.cpp"
#include "../Entities/FileEntity.cpp"
// 全局函数
extern void toDataAnalyseSystem();
extern void launchPoly();
extern void displayError();
extern void chooseOptiOrderProcessor();
extern void  displayErrorChartProcessor();
extern void saveResult();
// 全局变量
extern bool displayInfo;
extern GuiScreen *nowScreen;
extern int nowChooseDataIndex;
extern std::vector<std::string> dataFileNames;
extern FileEntity* nowFile;
class DataResScreen : public GuiScreen{
public:
    DataResScreen() {
        isActive = true;
        initControllers();
    }
    void onUpdate() const override {
        while (isActive) {
            BeginBatchDraw(); // 开始图像批量绘制
            setbkcolor(RGB(250, 250, 250)); // 绘制背景
            cleardevice();
            //绘制信息文本
            settextstyle(15, 0, _T("宋体"), 0, 0, 1000, false, false, false);
            settextcolor(BLACK); // 设置文本颜色
            outtextxy(10 ,400,("文件名:"+nowFile->filename).c_str());
            if (displayInfo) {
                outtextxy(10, 435, ("最优拟合阶次:" + std::to_string(nowFile->optiOrder)).c_str());
                outtextxy(10, 470, ("拟合误差均值:" + std::to_string(nowFile->meanOfOptiOrder)).c_str());
                outtextxy(10, 505, ("拟合误差方差:" + std::to_string(nowFile->varianceOfOptiOrder)).c_str());
            }
            for (GuiControllers *controller: controllersVector) {
                controller->drawController();
            }
            for(GuiLabel *label : labelVector){
                label->drawController();
            }
            EndBatchDraw();// 结束图形批量绘制
        }
        nowScreen->onUpdate();
    }
private:
    void initControllers(){
        GuiButton *backButton = new GuiButton(834, 400, 1014, 430, RGB(0, 122, 204), RGB(255, 255, 255), 30,
                                              _T("返回选择界面"),toDataAnalyseSystem);
        controllersVector.push_back(backButton);
        GuiButton *polyButton = new GuiButton(834, 440, 1014, 470, RGB(0, 122, 204), RGB(255, 255, 255), 30,
                                              _T("开始拟合"),launchPoly);
        controllersVector.push_back(polyButton);
        GuiButton *displayErrorButton = new GuiButton(834, 480, 1014, 510, RGB(0, 122, 204), RGB(255, 255, 255), 30,
                                              _T("显示误差图"),displayError);
        controllersVector.push_back(displayErrorButton);
        GuiButton *chooseOptiOrder = new GuiButton(834, 520, 1014, 550, RGB(0, 122, 204), RGB(255, 255, 255), 30,
                                                   _T("选择最优阶次"),chooseOptiOrderProcessor);
        controllersVector.push_back(chooseOptiOrder);
        GuiButton *displayErrorChart = new GuiButton(834, 560, 1014, 590, RGB(0, 122, 204), RGB(255, 255, 255), 30,
                                                     _T("显示差值特点"),displayErrorChartProcessor);
        controllersVector.push_back(displayErrorChart);
        GuiButton *saveResultButton= new GuiButton(834, 600, 1014, 630, RGB(0, 122, 204), RGB(255, 255, 255), 30,
                                                   _T("保存结果"),saveResult);
        controllersVector.push_back(saveResultButton);
    }
};