//
// Created by ly on 2024/1/29.
//
#pragma once

#include <minwindef.h>

class GuiControllers{
public:
    bool isActive;
    virtual void onMouseMove(int x , int y) = 0;
    virtual void onClick(int x , int y) = 0;
    virtual void drawController() = 0;
    virtual void onKeyPress(BYTE key) = 0;
    virtual ~GuiControllers() = default;
    void setControllerPassive() {
        this->isActive = false;
    }
};