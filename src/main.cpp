#include <iostream>
#include <thread>
#include "GuiComponents/GuiButton.cpp"
#include "GuiComponents/GuiScreen.cpp"
#include "Screens/WelcomeScreen.cpp"
//全局方法
extern void getUserInput();
//全局变量
GuiScreen* nowScreen;// 当前窗口
GuiScreen* lastScreen;// 上一个窗口
int main() {
    initgraph(1024,768); // 初始化窗口
    std::thread threadUserInput(getUserInput); // 开启用户输入线程
    nowScreen = new WelcomeScreen(); // 初始化登录界面
    nowScreen->onUpdate();
    threadUserInput.join();
    return 0;
}
