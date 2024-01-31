//
// Created by ly on 2024/1/29.
//
#pragma once

#include <vector>
#include <iostream>
#include <mutex>
#include "graphics.h"
#include "GuiLabel.cpp"
#include "GuiControllers.cpp"
class GuiScreen{
public:
    std::vector<GuiControllers *> controllersVector;
    std::vector<GuiLabel *> labelVector;
    bool isActive;
    virtual void onUpdate() const = 0; // ͼ����º���
    virtual ~GuiScreen() {

        for(GuiControllers* controller:controllersVector){
            delete controller;
        }
        for(GuiLabel* label:labelVector){
            delete label;
        }

    }// ������������
    void setScreenPassive(){// ���ò������
        isActive = false;
        for(GuiControllers* controller:controllersVector){
            controller->setControllerPassive();
        }
    }
};