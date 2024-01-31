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

//ȫ�ֱ���
extern GuiScreen *nowScreen;// ��ǰ����
//
void mouseMoveHandler(int x, int y);

void mouseClickHandler(int x, int y);

void keyDownHandler(BYTE vkcode);

void getUserInput() {
    ExMessage msg; // ������Ϣ
    while (true) {
        std::thread *thread = nullptr;
        // ���򰴼���Ϣ
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
            thread->detach();  // ����ʹ�� thread->joinable() ������߳��Ƿ������
            delete thread;     // �ͷ�ָ�룬�����ڴ�й©
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