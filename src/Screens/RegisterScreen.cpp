//
// Created by ly on 2024/1/29.
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
extern void RegisterProcessor();
extern void reduceRegister();
// 全局变量
extern GuiScreen *nowScreen;
extern GuiInputBox *usernameInputBox;
extern GuiInputBox *passwordInputBox;
extern GuiInputBox *repeatInputBox;
extern bool isDifferent;
extern bool isUserAlreadyExist;
extern bool isRegSuccess;
class RegisterScreen : public GuiScreen {
public:
    RegisterScreen() {
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
            //绘制提示
            settextstyle(20, 0, _T("宋体"), 0, 0, 1000, false, false, false);
            settextcolor(BLACK);
            outtextxy(200,80, _T("用户名(字母和数字组合 最多30个字符)"));
            outtextxy(200,240, _T("密码(字母和数字组合 最多30个字符)"));
            outtextxy(200,400, _T("请重复输入密码"));
            if (isDifferent){
                settextcolor(RED);
                outtextxy(200,380, _T("两次输入的密码不一致"));
            }
            if (isUserAlreadyExist){
                settextcolor(RED);
                outtextxy(200,60, _T("用户已存在"));
            }
            if (isRegSuccess){
                settextcolor(RGB(25,202,173));
                outtextxy(200,60,_T("注册成功"));
            }
            EndBatchDraw();// 结束图形批量绘制
        }
        nowScreen->onUpdate();
    }

private:
    void initControllers() {
        usernameInputBox = new GuiInputBox(200, 100, 824, 160, RGB(231, 230, 231), RGB(0, 0, 0),
                                                        RGB(243, 238, 240), 40, 30, false);
        controllersVector.push_back(usernameInputBox);
        passwordInputBox = new GuiInputBox(200, 260, 824, 320, RGB(231, 230, 231), RGB(0, 0, 0),
                                                        RGB(243, 238, 240), 40, 30, false);
        controllersVector.push_back(passwordInputBox);
        repeatInputBox = new GuiInputBox(200, 420, 824, 480, RGB(231, 230, 231), RGB(0, 0, 0),
                                                        RGB(243, 238, 240), 40, 30, false);
        controllersVector.push_back(repeatInputBox);
        GuiButton *registerButton = new GuiButton(80, 520, 944, 580, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                                   _T("确认注册"),
                                                  RegisterProcessor);
        controllersVector.push_back(registerButton);
        GuiButton *backButton = new GuiButton(80, 600, 944, 660, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                               _T("返回"),reduceRegister);
        controllersVector.push_back(backButton);
    }
};