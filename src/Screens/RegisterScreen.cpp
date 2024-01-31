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
// ȫ�ֺ���
extern void RegisterProcessor();
extern void reduceRegister();
// ȫ�ֱ���
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
            //������ʾ
            settextstyle(20, 0, _T("����"), 0, 0, 1000, false, false, false);
            settextcolor(BLACK);
            outtextxy(200,80, _T("�û���(��ĸ��������� ���30���ַ�)"));
            outtextxy(200,240, _T("����(��ĸ��������� ���30���ַ�)"));
            outtextxy(200,400, _T("���ظ���������"));
            if (isDifferent){
                settextcolor(RED);
                outtextxy(200,380, _T("������������벻һ��"));
            }
            if (isUserAlreadyExist){
                settextcolor(RED);
                outtextxy(200,60, _T("�û��Ѵ���"));
            }
            if (isRegSuccess){
                settextcolor(RGB(25,202,173));
                outtextxy(200,60,_T("ע��ɹ�"));
            }
            EndBatchDraw();// ����ͼ����������
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
                                                   _T("ȷ��ע��"),
                                                  RegisterProcessor);
        controllersVector.push_back(registerButton);
        GuiButton *backButton = new GuiButton(80, 600, 944, 660, RGB(0, 122, 204), RGB(255, 255, 255), 40,
                                               _T("����"),reduceRegister);
        controllersVector.push_back(backButton);
    }
};