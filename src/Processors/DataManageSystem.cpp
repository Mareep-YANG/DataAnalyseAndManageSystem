//
// Created by ly on 2024/1/31.
//
#include <fstream>
#include "../Entities/FileEntity.cpp"
#include "../GuiComponents/GuiScreen.cpp"
#include "../Screens/DataAnalyseScreen.cpp"
#include "../Screens/DataManageScreen.cpp"
#include "../Entities/SavedDataEntity.cpp"
//ȫ�ֱ���
extern FileEntity* nowFile;
std::vector<SavedDataEntity> savedDatas;
int nowChooseSavedDataIndex=0;
//ȫ�ֺ���
extern void toNextScreen(GuiScreen *nextScreen);
bool  ifViewData = false;
void viewData(){
    ifViewData = !ifViewData;
}
void deleteDataProcessor(){
    std::string filename = savedDatas[nowChooseSavedDataIndex].filename;
    std::string line;
    std::ifstream infile("datainfo.dat");
    std::ofstream outfile("datainfo.dat",std::ios::trunc);
    while (std::getline(infile, line)) {
        std::string filenameInFile = line.substr(0, line.find(' '));
        if (filename != filenameInFile) {
            outfile << line << std::endl;
        }
    }
    savedDatas.erase(savedDatas.begin() +nowChooseSavedDataIndex);
    nowChooseSavedDataIndex=0;
    outfile.close();
}
void chooseUpManage() {
    // ���� �����ص���0
    if (nowChooseSavedDataIndex == savedDatas.size() - 1) {
        nowChooseSavedDataIndex = 0;
    } else {
        nowChooseSavedDataIndex++;
    }
}

void chooseDownManage() {
    // ���� ���׻ص������һ��
    if (nowChooseSavedDataIndex == 0) {
        nowChooseSavedDataIndex = savedDatas.size() - 1;
    } else {
        nowChooseSavedDataIndex--;
    }
}
bool ifDataAlreadyExist(std::string dataname) {
    std::ifstream infile("datainfo.dat");
    std::string line;
    while (std::getline(infile, line)) {
        std::string filenameInFile = line.substr(0, line.find(' '));
        if (dataname == filenameInFile) {
            return true;
        }
    }
    return false;
}
void toManageScreen(){
    savedDatas.clear();
    const char *filename = "datainfo.dat";
    std::ifstream infile(filename);
    if (!infile) { // �ļ��������ж��ļ��Ƿ����
        // �����ļ�
        std::ofstream outfile(filename);
        if (!outfile) {
            exit(1);
        }
    }
    // ��������
    std::string line;
    while (std::getline(infile, line)) { // ���ļ�
        std::string filename = line.substr(0, line.find(' '));
        std::string optiOrder = line.substr(line.find(' ') + 1);
        std::string meanOfOptiOrder = line.substr(line.find(' ') + 2);
        std::string varianceOfOptiOrder = line.substr(line.find(" ")+3);
        savedDatas.push_back(SavedDataEntity(filename, std::stoi(optiOrder), std::stof(meanOfOptiOrder), std::stof(varianceOfOptiOrder)));
    }
    toNextScreen(new DataManageScreen());
}
void saveResult(){
    const char *filename = "datainfo.dat";
    std::ifstream infile(filename);
    if (!infile) { // �ļ��������ж��ļ��Ƿ����
        // �����ļ�
        std::ofstream outfile(filename);
        if (!outfile) {
            exit(1);
        }
    }
// �ļ������
    std::ofstream outfile(filename, std::ios::app);
    if (!outfile) {
        exit(1);
    }
    else{
        if (ifDataAlreadyExist(nowFile->filename)){
            return;
        }
        outfile << nowFile->filename << " " << nowFile->optiOrder <<" "<<nowFile->meanOfOptiOrder<<" "<<nowFile->varianceOfOptiOrder<<std::endl;
    }
    toNextScreen(new DataAnalyseScreen());
}