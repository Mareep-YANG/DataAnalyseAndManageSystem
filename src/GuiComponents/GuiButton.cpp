//
// Created by ly on 2024/1/29.
//
#pragma once
#include "GuiControllers.cpp"
#include "graphics.h"
#include <thread>
class GuiButton : public GuiControllers{
public:
    int left; // ����X����
    int top; // ����Y����
    int right; // ����X����
    int bottom;// ����Y����
    int text_height; // ���ָ߶�(��С)
    COLORREF originColor; //���õİ�ť��ɫ
    COLORREF color; // ʵ����Ⱦ��ť��ɫ
    COLORREF text_color;// ������ɫ
    TCHAR text[20]; // ��������
    // ��ť�Ĺ��캯��
    GuiButton(int left, int top, int right, int bottom, COLORREF color, COLORREF text_color, int text_height,
              TCHAR text[20], void (&func)()) {
        this->isActive = true;
        this->left = left;
        this->top = top;
        this->right = right;
        this->bottom = bottom;
        this->originColor = color;
        this->color = color;
        this->text_color = text_color;
        strcpy(this->text, text);
        this->ButtonProcessor = func;
        this->text_height = text_height;
    }

    // ���ư�ť�ĺ���
    void drawController() override {
        setfillcolor(color);
        solidrectangle(left, top, right, bottom);
        settextcolor(text_color);
        settextstyle(text_height, 0, _T("����"), 0, 0, 1000, false, false, false);
        setbkmode(TRANSPARENT);
        outtextxy(left + (right - left) / 2 - textwidth(text) / 2, (bottom - top) / 2 - textheight(text) / 2 + top, text);
    }

    void onClick(int x, int y)  override {
        if (x >= left && x <= right && y >= top && y <= bottom && this->isActive) {
            ButtonProcessor();
        }
    }
    void onMouseMove(int x, int y) override {
        if (x >= left && x <= right && y >= top && y <= bottom && this->isActive) {
            color = RGB(190,231,233);
        } else {
            color = this->originColor;
        }
    }


    void onKeyPress(BYTE key) override{

    }

private:
    void (*ButtonProcessor)();
};