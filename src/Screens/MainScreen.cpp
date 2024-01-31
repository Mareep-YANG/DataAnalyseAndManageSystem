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
// ȫ�ֺ���
extern void toDataAnalyseSystem();
extern void logOutProcessor();
extern void toManageScreen();
// ȫ�ֱ���
extern GuiScreen *nowScreen;
class MainScreen : public GuiScreen{
public:
    MainScreen() {
        isActive = true;
        initControllers();
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
            settextcolor(WHITE);
            outtextxy(40, 718, _T("C���Գ������A�γ����  ����:** �༶:��****"));
            EndBatchDraw();// ����ͼ����������
        }
        nowScreen->onUpdate();
    }
private:
    void initControllers(){
        GuiButton *dataAnalyseButton = new GuiButton(80, 200, 944, 260, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                              _T("���ݷ���ϵͳ"),toDataAnalyseSystem);
        controllersVector.push_back(dataAnalyseButton);
        GuiButton *dataManageButton = new GuiButton(80, 360, 944, 420, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                                    _T("���ݹ���ϵͳ"),toManageScreen);
        controllersVector.push_back(dataManageButton);
        GuiButton *logOutButton = new GuiButton(80, 520, 944, 580, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                                    _T("�˳���¼"),logOutProcessor);
        controllersVector.push_back(logOutButton);
    }
};