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
extern void toMainScreen();
extern void launchDataAnalyce();
extern void chooseUp();
extern void chooseDown();
// ȫ�ֱ���
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
            outtextxy(512 - textwidth("���ݴ���ϵͳ") / 2, 30 - textheight("���ݴ���ϵͳ") / 2,
                      _T("���ݴ���ϵͳ"));
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
            // �����ļ���
            settextcolor(BLACK);
            settextstyle(30, 0, _T("����"), 0, 0, 1000, false, false, false);
            outtextxy(250, 100, _T("��ѡ��Ҫ�����������ļ�:"));
            outtextxy(250+(1024-250)/2- textwidth(dataFileNames[nowChooseDataIndex].c_str())/2,200, dataFileNames[nowChooseDataIndex].c_str());
            EndBatchDraw();// ����ͼ����������
        }
        nowScreen->onUpdate();
    }
private:
    void initControllers(){
        GuiButton *backButton = new GuiButton(40, 100, 240, 350, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                                     _T("�������˵�"),toMainScreen);
        controllersVector.push_back(backButton);
        GuiButton *launchButton = new GuiButton(40, 400, 240, 650, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                              _T("��������"),launchDataAnalyce);
        controllersVector.push_back(launchButton);
        GuiButton *upButton = new GuiButton(400, 280, 874, 340, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                            _T("��һ��"),chooseUp);
        controllersVector.push_back(upButton);
        GuiButton *downButton = new GuiButton(400, 440, 874, 500, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                            _T("��һ��"),chooseDown);
        controllersVector.push_back(downButton);
    }
};