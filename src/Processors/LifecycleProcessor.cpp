#pragma once
#include <cstdlib>
#include <iostream>
#include <mutex>
#include "../GuiComponents/GuiScreen.cpp"
#include "../Screens/DataAnalyseScreen.cpp"
#include "../Screens/MainScreen.cpp"
std::mutex Mutex;
//
// Created by ly on 2024/1/29.
//
// 全局变量
extern GuiScreen* nowScreen;// 当前窗口
extern GuiScreen* lastScreen;// 上一个窗口
void exitProcessor(){
    exit(0);
}
void toNextScreen(GuiScreen* nextScreen){
    delete lastScreen;
    lastScreen = nowScreen;
    nowScreen = nextScreen;
    lastScreen->setScreenPassive();
}
void toMainScreen(){
    toNextScreen(new MainScreen());
};

