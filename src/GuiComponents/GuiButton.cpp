//
// Created by ly on 2024/1/29.
//
#pragma once
#include "GuiControllers.cpp"
#include "graphics.h"
#include <thread>
class GuiButton : public GuiControllers{
public:
    int left; // 左上X坐标
    int top; // 左上Y坐标
    int right; // 右下X坐标
    int bottom;// 右下Y坐标
    int text_height; // 文字高度(大小)
    COLORREF originColor; //设置的按钮颜色
    COLORREF color; // 实际渲染按钮颜色
    COLORREF text_color;// 文字颜色
    TCHAR text[20]; // 文字内容
    // 按钮的构造函数
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

    // 绘制按钮的函数
    void drawController() override {
        setfillcolor(color);
        solidrectangle(left, top, right, bottom);
        settextcolor(text_color);
        settextstyle(text_height, 0, _T("宋体"), 0, 0, 1000, false, false, false);
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