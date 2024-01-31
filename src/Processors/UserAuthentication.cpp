#pragma once

#include <iostream>
#include <fstream>
#include "graphics.h"
#include "../GuiComponents/GuiScreen.cpp"
#include "../GuiComponents/GuiInputBox.cpp"
#include "../Screens/RegisterScreen.cpp"
#include "../Screens/WelcomeScreen.cpp"
#include "../Screens/LoginScreen.cpp"
#include "../Screens/MainScreen.cpp"

//
// Created by ly on 2024/1/29.
//
// 全局变量
extern GuiScreen *nowScreen;
GuiInputBox *usernameInputBox;
GuiInputBox *passwordInputBox;
GuiInputBox *repeatInputBox;
GuiInputBox *loginUserName;
GuiInputBox *loginPassword;
bool isDifferent = false;
bool isUserAlreadyExist = false;
bool isRegSuccess = false;
bool isLoginSuccess = false;
bool isPasswordWrong = false;
// 全局方法
extern void toNextScreen(GuiScreen *nextScreen);
void logOutProcessor(){
    toNextScreen(new WelcomeScreen());
}
void beginLoginProcessor() {
    isUserAlreadyExist = true; // 赋初值 防止直接显示不存在
    const char *filename = "userinfo.dat";
    std::ifstream infile(filename);
    if (!infile) { // 文件输入流判断文件是否存在
        // 创建文件
        std::ofstream outfile(filename);
        if (!outfile) {
            exit(1);
        }
    }
    toNextScreen(new LoginScreen());
}
//TODO:增加密码错误提示
bool ifUserAlreadyExist(std::string username) {
    std::ifstream infile("userinfo.dat");
    std::string line;
    while (std::getline(infile, line)) {
        std::string usernameInFile = line.substr(0, line.find(' '));
        if (username == usernameInFile) {
            return true;
        }
    }
    return false;
}

void loginProcessor() {
    std::string username = std::string(loginUserName->text);
    std::string password = std::string(loginPassword->text);
    // 构造账号密码字符串
    if (username.empty() || password.empty()) {// 检测非空
        return;
    }
    if (!ifUserAlreadyExist(username)) { // 检测是否存在
        isUserAlreadyExist = false;
        return;
    } else {
        std::hash<std::string> hasher;
        std::ifstream infile("userinfo.dat");
        std::string line;
        while (std::getline(infile, line)) { // 读文件
            std::string usernameInFile = line.substr(0, line.find(' '));
            std::string passwordInFile = line.substr(line.find(' ') + 1);
            if (username == usernameInFile && std::to_string(hasher(username + password)) == passwordInFile) { // 加盐hash鉴权
                isLoginSuccess = true;
                isUserAlreadyExist = true;
                isPasswordWrong = false;
                std::chrono::seconds duration(2);
                std::this_thread::sleep_for(duration);// 等待两秒显示
                isLoginSuccess = false;
                toNextScreen(new MainScreen());// 切换到主菜单
                return;
            } else{
                isPasswordWrong = true;
            }
        }
        isUserAlreadyExist = true;
    }
}

void beginRegisterProcessor() { // 注册开始函数
    isUserAlreadyExist = false;
    const char *filename = "userinfo.dat";
    std::ifstream infile(filename);
    if (!infile) { // 文件输入流判断文件是否存在
        // 创建文件
        std::ofstream outfile(filename);
        if (!outfile) {
            exit(1);
        }
    }

    // 跳转到注册界面
    toNextScreen(new RegisterScreen());
}


void RegisterProcessor() {
    std::string username = std::string(usernameInputBox->text);
    std::string password = std::string(passwordInputBox->text);
    std::string repeat = std::string(repeatInputBox->text);
    if (username.empty() || password.empty() || repeat.empty()) {
        isDifferent = false;
        isUserAlreadyExist = false;
        return;
    }
    if (ifUserAlreadyExist(username)) {
        isUserAlreadyExist = true;
        return;
    }
    if (password != repeat) {
        isDifferent = true;
        isUserAlreadyExist = false;
        return;
    } else {
        isRegSuccess = true;
        isDifferent = false;
        isUserAlreadyExist = false;
        // 写入文件
        std::hash<std::string> hasher;
        std::ofstream outfile("userinfo.dat", std::ios::app);
        outfile << username << " " << std::to_string(hasher(username + password)) << std::endl;
        outfile.close();
        std::chrono::seconds duration(2);
        std::this_thread::sleep_for(duration);
        isRegSuccess = false;
        toNextScreen(new WelcomeScreen());
    }
}

void reduceRegister() {
    toNextScreen(new WelcomeScreen());
}

