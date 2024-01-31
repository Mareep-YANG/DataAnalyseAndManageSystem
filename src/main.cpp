#include <iostream>
#include <thread>
#include "GuiComponents/GuiButton.cpp"
#include "GuiComponents/GuiScreen.cpp"
#include "Screens/WelcomeScreen.cpp"
//ȫ�ַ���
extern void getUserInput();
//ȫ�ֱ���
GuiScreen* nowScreen;// ��ǰ����
GuiScreen* lastScreen;// ��һ������
int main() {
    initgraph(1024,768); // ��ʼ������
    std::thread threadUserInput(getUserInput); // �����û������߳�
    nowScreen = new WelcomeScreen(); // ��ʼ����¼����
    nowScreen->onUpdate();
    threadUserInput.join();
    return 0;
}
