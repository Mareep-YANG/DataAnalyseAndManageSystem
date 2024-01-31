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
// ȫ�ֱ���
extern GuiScreen* nowScreen;// ��ǰ����
extern GuiScreen* lastScreen;// ��һ������
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

