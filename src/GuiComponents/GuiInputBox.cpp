//
// Created by ly on 2024/1/29.
//
#pragma once
#include <iostream>
#include "graphics.h"
#include "GuiControllers.cpp"
class GuiInputBox : public GuiControllers{
public:
    int left; // 左上X坐标
    int top; // 左上Y坐标
    int right; // 右下X坐标
    int bottom; // 右下Y坐标
    int text_height; // 文字高度(大小)
    COLORREF borderColor; // 输入框边框颜色
    COLORREF textColor; // 文字颜色
    COLORREF backgroundColor; // 输入框背景颜色
    TCHAR text[50]; // 文字内容
    int maxLength; // 输入框最大长度
    bool isPassword; // 是否是密码输入框
    bool hasFocus; // 是否拥有焦点
    int cursorPosition; // 光标位置

    // 输入框的构造函数
    GuiInputBox(int left, int top, int right, int bottom, COLORREF borderColor, COLORREF textColor,
                COLORREF backgroundColor, int text_height, int maxLength, bool isPassword) {
        this->isActive = true;
        this->left = left;
        this->top = top;
        this->right = right;
        this->bottom = bottom;
        this->borderColor = borderColor;
        this->textColor = textColor;
        this->backgroundColor = backgroundColor;
        this->text_height = text_height;
        this->maxLength = maxLength;
        this->isPassword = isPassword;
        this->hasFocus = false;
        this->cursorPosition = 0;
        memset(this->text, 0, sizeof(this->text));
    }

    // 绘制输入框的函数
    void drawController() override {
  //      std::cout << text<<" "<<cursorPosition<<std::endl;
        setfillcolor(backgroundColor);
        solidrectangle(left, top, right, bottom);
        setcolor(borderColor);
        rectangle(left, top, right, bottom);
        settextcolor(textColor);
        settextstyle(text_height, 0, _T("宋体"), 0, 0, 1000, false, false, false);
        setbkmode(TRANSPARENT);

        if (hasFocus && isActive) {
            // 绘制光标
            setcolor(BLACK);
            line(left + 5 + textwidth(text), top + 5, left + 5 + textwidth(text),
                 bottom - 5);
        }

        if (isPassword) {
            // 如果是密码输入框，显示*代替实际字符
            const int passwordCharWidth = 20; // 定义*的宽度
            int length = _tcslen(text);
            for (int i = 0; i < length; ++i) {
                outtextxy(left + 5 + i * passwordCharWidth, top + (bottom - top) / 2 - textheight(text) / 2,
                          _T("*"));
            }
        } else {
            outtextxy(left + 5, top + (bottom - top) / 2 - textheight(text) / 2, text);
        }
    }

    void onClick(int x, int y) override {
        if (x >= left && x <= right && y >= top && y <= bottom) {
            isActive = true;
            hasFocus = true;
        } else {
            hasFocus = false;
        }
    }

    void onKeyPress(BYTE key) override{
        if (key == VK_BACK){
            if (hasFocus && cursorPosition > 0) {
                cursorPosition -= 1;
                text[cursorPosition] = '\0';
            }
        }
        else if(key == VK_RETURN){
            hasFocus = false;
        }
        else if(key>=65 && key <= 90 || key >= 48 && key <=57 ){
            if (hasFocus && cursorPosition < maxLength - 1) {
                text[cursorPosition] = MapVirtualKey(key, MAPVK_VK_TO_CHAR);
                cursorPosition++;
            }
        }
    }
    void onMouseMove(int x , int y) override{
    }
};
