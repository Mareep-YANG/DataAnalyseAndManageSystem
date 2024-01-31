//
// Created by ly on 2024/1/29.
//
#pragma once

#include "../GuiComponents/GuiScreen.cpp"
#include "../GuiComponents/GuiButton.cpp"
#include "../GuiComponents/GuiControllers.cpp"
#include "graphics.h"
#include <vector>
#include <stack>
#include <iostream>

// ȫ�ֺ���
extern void beginLoginProcessor();

extern void beginRegisterProcessor();

extern void exitProcessor();
extern GuiScreen* nowScreen;// ��ǰ����
// ȫ�ֱ���
class WelcomeScreen : public GuiScreen {
public:
    WelcomeScreen() {
        isActive = true;
        initButtons();
    }

    void onUpdate() const override {
        while (isActive) {
            BeginBatchDraw(); // ��ʼͼ����������
            setbkcolor(RGB(250, 250, 250)); // ���Ʊ���
            cleardevice();
            // ���Ʊ�����
            setfillcolor(RGB(243, 238, 240));
            solidrectangle(0, 0, 1024, 60);
            // ���Ʒָ���
            setfillcolor(RGB(231, 230, 231));
            solidrectangle(0, 60, 1024, 61);
            //���Ʊ�������
            settextcolor(BLACK);
            setbkmode(TRANSPARENT);//�������ֱ���͸��
            settextstyle(40, 0, _T("����"), 0, 0, 1000, false, false, false);
            outtextxy(512 - textwidth("���ݴ�������Ϣ����ϵͳ") / 2, 30 - textheight("���ݴ�������Ϣ����ϵͳ") / 2,
                      _T("���ݴ�������Ϣ����ϵͳ"));
            // ������Ϣ��
            setfillcolor(RGB(140, 199, 181));
            solidrectangle(0, 708, 1024, 768);
            // ���Ʒָ���
            setfillcolor(RGB(231, 230, 231));
            solidrectangle(0, 707, 1024, 708);
            for (GuiControllers *controller: controllersVector) {
                controller->drawController();
            }
            outtextxy(40,718,_T("C���Գ������A�γ����  ����:** �༶:��****"));
            EndBatchDraw();// ����ͼ����������
        }
        nowScreen->onUpdate();
    }

private:
    void initButtons() {
        GuiButton *loginButton = new GuiButton(80, 160, 944, 220, RGB(0, 122, 204), RGB(255, 255, 255), 40, _T("��¼"),
                                               beginLoginProcessor);
        controllersVector.push_back(loginButton);
        GuiButton *registerButton = new GuiButton(80, 320, 944, 380, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                                  _T("ע��"),
                                                  beginRegisterProcessor);

        controllersVector.push_back(registerButton);
        GuiButton *exitButton = new GuiButton(80, 480, 944, 540, RGB(0, 122, 204), RGB(255, 255, 255), 40, _T("�˳�"),
                                              exitProcessor);
        controllersVector.push_back(exitButton);
    }
};
