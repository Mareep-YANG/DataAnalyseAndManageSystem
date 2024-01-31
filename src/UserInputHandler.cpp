//
// Created by ly on 2024/1/29.
//
#include "graphics.h"
#include <vector>
#include <iostream>
#include <mutex>
#include "GuiComponents/GuiButton.cpp"
#include "GuiComponents/GuiControllers.cpp"
#include "GuiComponents/GuiScreen.cpp"

//全局变量
extern GuiScreen *nowScreen;// 当前窗口
//
void mouseMoveHandler(int x, int y);

void mouseClickHandler(int x, int y);

void keyDownHandler(BYTE vkcode);

void getUserInput() {
    ExMessage msg; // 定义消息
    while (true) {
        std::thread *thread = nullptr;
        // 鼠标或按键消息
        msg = getmessage(EX_MOUSE | EX_KEY);
        switch (msg.message) {
            case WM_MOUSEMOVE:
                thread = new std::thread(mouseMoveHandler, msg.x, msg.y);
                break;
            case WM_LBUTTONDOWN:
                thread = new std::thread(mouseClickHandler, msg.x, msg.y);
                break;
            case WM_KEYDOWN:
                thread = new std::thread(keyDownHandler, msg.vkcode);
                break;
        }
        if (thread) {
            thread->detach();  // 或者使用 thread->joinable() 来检查线程是否可连接
            delete thread;     // 释放指针，避免内存泄漏
        }
    }
}

void mouseMoveHandler(int x, int y) {
    for (GuiControllers *controller: nowScreen->controllersVector) {
        if (controller->isActive) {
            controller->onMouseMove(x, y);
        }
    }
}

void mouseClickHandler(int x, int y) {
    for (GuiControllers *controller: nowScreen->controllersVector) {
        if (controller->isActive) {
            controller->onClick(x, y);
        }
    }
}

void keyDownHandler(BYTE vkcode) {
    for (GuiControllers *controller: nowScreen->controllersVector) {
        if (controller->isActive) {
            controller->onKeyPress(vkcode);
        }
    }
}