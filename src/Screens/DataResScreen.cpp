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
// ȫ�ֺ���
extern void toDataAnalyseSystem();
extern void launchPoly();
extern void displayError();
extern void chooseOptiOrderProcessor();
extern void  displayErrorChartProcessor();
extern void saveResult();
// ȫ�ֱ���
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
            BeginBatchDraw(); // ��ʼͼ����������
            setbkcolor(RGB(250, 250, 250)); // ���Ʊ���
            cleardevice();
            //������Ϣ�ı�
            settextstyle(15, 0, _T("����"), 0, 0, 1000, false, false, false);
            settextcolor(BLACK); // �����ı���ɫ
            outtextxy(10 ,400,("�ļ���:"+nowFile->filename).c_str());
            if (displayInfo) {
                outtextxy(10, 435, ("������Ͻ״�:" + std::to_string(nowFile->optiOrder)).c_str());
                outtextxy(10, 470, ("�������ֵ:" + std::to_string(nowFile->meanOfOptiOrder)).c_str());
                outtextxy(10, 505, ("�������:" + std::to_string(nowFile->varianceOfOptiOrder)).c_str());
            }
            for (GuiControllers *controller: controllersVector) {
                controller->drawController();
            }
            for(GuiLabel *label : labelVector){
                label->drawController();
            }
            EndBatchDraw();// ����ͼ����������
        }
        nowScreen->onUpdate();
    }
private:
    void initControllers(){
        GuiButton *backButton = new GuiButton(834, 400, 1014, 430, RGB(0, 122, 204), RGB(255, 255, 255), 30,
                                              _T("����ѡ�����"),toDataAnalyseSystem);
        controllersVector.push_back(backButton);
        GuiButton *polyButton = new GuiButton(834, 440, 1014, 470, RGB(0, 122, 204), RGB(255, 255, 255), 30,
                                              _T("��ʼ���"),launchPoly);
        controllersVector.push_back(polyButton);
        GuiButton *displayErrorButton = new GuiButton(834, 480, 1014, 510, RGB(0, 122, 204), RGB(255, 255, 255), 30,
                                              _T("��ʾ���ͼ"),displayError);
        controllersVector.push_back(displayErrorButton);
        GuiButton *chooseOptiOrder = new GuiButton(834, 520, 1014, 550, RGB(0, 122, 204), RGB(255, 255, 255), 30,
                                                   _T("ѡ�����Ž״�"),chooseOptiOrderProcessor);
        controllersVector.push_back(chooseOptiOrder);
        GuiButton *displayErrorChart = new GuiButton(834, 560, 1014, 590, RGB(0, 122, 204), RGB(255, 255, 255), 30,
                                                     _T("��ʾ��ֵ�ص�"),displayErrorChartProcessor);
        controllersVector.push_back(displayErrorChart);
        GuiButton *saveResultButton= new GuiButton(834, 600, 1014, 630, RGB(0, 122, 204), RGB(255, 255, 255), 30,
                                                   _T("������"),saveResult);
        controllersVector.push_back(saveResultButton);
    }
};