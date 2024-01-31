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
// ȫ�ֺ���
extern void toMainScreen();
extern void chooseUpManage();
extern void chooseDownManage();
extern void deleteDataProcessor();
extern void viewData();
// ȫ�ֱ���
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
            outtextxy(512 - textwidth("��Ϣ����ϵͳ") / 2, 30 - textheight("��Ϣ����ϵͳ") / 2,
                      _T("��Ϣ����ϵͳ"));
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
            settextcolor(BLACK);
            settextstyle(40, 0, _T("����"), 0, 0, 1000, false, false, false);
            outtextxy(40,400,"��ǰ�洢��������:");
            outtextxy(180,480,std::to_string(savedDatas.size()).c_str());
            outtextxy(500,400,"��ǰѡ�е������ļ���");
            if (!savedDatas.empty()){
                outtextxy(640,480,savedDatas[nowChooseSavedDataIndex].filename.c_str());
            }
            if (ifViewData&&!savedDatas.empty()){
                settextstyle(30, 0, _T("����"), 0, 0, 1000, false, false, false);
                outtextxy(40,560,("���Ž���:"+std::to_string(savedDatas[nowChooseSavedDataIndex].optiOrder)).c_str());
                outtextxy(40,590,("���Ž������������ֵ:"+std::to_string(savedDatas[nowChooseSavedDataIndex].meanOfOptiOrder)).c_str());
                outtextxy(40,620,("���Ž������������:"+std::to_string(savedDatas[nowChooseSavedDataIndex].varianceOfOptiOrder)).c_str());
            }
            EndBatchDraw();// ����ͼ����������
        }
        nowScreen->onUpdate();
    }
private:
    void initControllers(){
        GuiButton *backButton = new GuiButton(40, 100, 240, 350, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                              _T("�������˵�"),toMainScreen);
        controllersVector.push_back(backButton);
        GuiButton *deleteDataButton = new GuiButton(260, 100, 460, 350, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                                _T("ɾ��������"),deleteDataProcessor);
        controllersVector.push_back(deleteDataButton);
        GuiButton *viewDataButton = new GuiButton(480, 100, 680, 350, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                                    _T("�鿴����"),viewData);
        controllersVector.push_back(viewDataButton);
        GuiButton *upButton = new GuiButton(700, 100, 984, 160, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                            _T("��һ��"),chooseUpManage);
        controllersVector.push_back(upButton);
        GuiButton *downButton = new GuiButton(700, 290, 984, 350, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                              _T("��һ��"),chooseDownManage);
        controllersVector.push_back(downButton);
    }
};