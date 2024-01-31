//
// Created by ly on 2024/1/30.
//
#pragma once

#include <fstream>
#include <cmath>
#include <mutex>
#include "../GuiComponents/GuiScreen.cpp"
#include "../Screens/DataAnalyseScreen.cpp"
#include "filesystem"
#include "../Screens/DataResScreen.cpp"
#include "../Entities/FileEntity.cpp"
#include "../GuiComponents/GuiLineChart.cpp"
#include "../GuiComponents/GuiHistogram.cpp"
#include "../GuiComponents/GuiLabel.cpp"
namespace fs = std::filesystem;
extern std::mutex Mutex;
//全局函数
extern void toNextScreen(GuiScreen *nextScreen);

extern void polyfit(FileEntity *FILE, int poly_n);

extern double fx(double x, double coeffs[], int degree);

//全局变量
const std::string dataPath = "./data";
std::vector<std::string> dataFileNames;
int nowChooseDataIndex = 0;
FileEntity *nowFile;
bool polySuccess = false;
bool displayInfo = false;
void toDataAnalyseSystem() {
    dataFileNames.clear();
    nowChooseDataIndex = 0;
    try {
        // 如果目录不存在，则创建
        if (!fs::exists(dataPath)) {
            fs::create_directory(dataPath);
        }

        // 遍历目录中的所有文件
        for (const auto &entry: fs::directory_iterator(dataPath)) {
            if (entry.is_regular_file()) {
                dataFileNames.push_back(entry.path().filename().string());
            }
        }
    } catch (const fs::filesystem_error &ex) {
        std::cerr << "Error accessing directory: " << ex.what() << std::endl;
        exit(1);
    }
    toNextScreen(new DataAnalyseScreen());
}

void chooseUp() {
    // 增加 触顶回弹到0
    if (nowChooseDataIndex == dataFileNames.size() - 1) {
        nowChooseDataIndex = 0;
    } else {
        nowChooseDataIndex++;
    }
}

void chooseDown() {
    // 减少 触底回弹到最后一个
    if (nowChooseDataIndex == 0) {
        nowChooseDataIndex = dataFileNames.size() - 1;
    } else {
        nowChooseDataIndex--;
    }
}

void launchDataAnalyce() {
    displayInfo = false;
    polySuccess = false;
    std::vector<std::vector<double>> data;
    //构造出目标文件的路径
    const std::string targetFilePath = dataPath + "/" + dataFileNames[nowChooseDataIndex];
    // 打开文件
    std::ifstream infile(targetFilePath);
    std::string line;
    if (!infile.is_open()) {
//        std::cerr << "Error opening file: " << targetFilePath << std::endl;
        return;
    }
    while (std::getline(infile, line)) {
        std::string x_str, y_str;
        std::istringstream iss(line);
        if (iss >> x_str >> y_str) {
            double x = std::stod(x_str);
            double y = std::stod(y_str);
            data.push_back({x, y});
        }
    }
    nowFile = new FileEntity(dataFileNames[nowChooseDataIndex], data);
    toNextScreen(new DataResScreen());
    GuiLineChart *originChart = new GuiLineChart(nowFile->data, RGB(0, 0, 0), 50, 10, 950, 300);
    nowScreen->labelVector.push_back(originChart);

    infile.close();
}

int COLOR[16] = {BLACK, BLUE, GREEN, CYAN, RED, MAGENTA, BROWN, LIGHTGRAY, DARKGRAY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN,
                 LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE};
void launchPoly() {
    //弹窗输入最大拟合阶数
    char buffer[10];
    int MaxOrder = 0;
    InputBox(buffer, 10, "请输入最大拟合阶数");
    // 使用 strtol 进行转换
    char *endptr;
    long result = strtol(buffer, &endptr, 10);
    // 检查转换是否成功
    if (*endptr != '\0') {
        exit(1);
    } else {
        // 转换成功
        MaxOrder = static_cast<int>(result);
        if (MaxOrder <=0){
            return;
        }
        for (int order = 1; order <= MaxOrder; order++) {
            polyfit(nowFile, order);
        }
        for (int order = 1; order <= MaxOrder; order++) {
            std::vector<double> v;
            std::vector<double> fiterrorVector;
            double fiterror = 0;
            std::vector<std::vector<double>> data;
            for (int i = 0; i < nowFile->data.size(); i++) {
                v.push_back(fx(nowFile->data[i][0], nowFile->polyCoeff[order], order));
                fiterror += std::pow(v[i] - nowFile->data[i][1], 2);
                fiterrorVector.push_back(nowFile->data[i][1]-v[i]);
                data.push_back({nowFile->data[i][0], v[i]});
            }
            nowFile->fitErrors.push_back(fiterrorVector);
            nowFile->fity.push_back(v);
            nowFile->fitError.push_back(fiterror);
            GuiLineChart *polyChart = new GuiLineChart(data, COLOR[order % 16], 50, 10, 950, 300);
            nowScreen->labelVector.push_back(polyChart);

            polySuccess = true;
        }
        nowFile->MaxOrder = MaxOrder;

    }
}

void displayError() {
    if (polySuccess) {
        GuiHistogram *errorChart = new GuiHistogram(nowFile->fitError, 200, 400, 824, 700);
        nowScreen->labelVector.push_back(errorChart);

    }
}

double calculateVariance(FileEntity *file) {
    double sum = 0;
    for (double d: file->fitErrors[file->optiOrder - 1]) {
        sum += std::pow(d - file->meanOfOptiOrder, 2);
    }
    return sum / file->data.size();
}

void chooseOptiOrderProcessor() {
    if (polySuccess) {
//弹窗输入最优拟合阶数
        char buffer[10];
        int optiOrder = 0;
        InputBox(buffer, 10, "请输入最优的拟合阶数");
        // 使用 strtol 进行转换
        char *endptr;
        long result = strtol(buffer, &endptr, 10);
        // 检查转换是否成功
        if (*endptr != '\0') {
            exit(1);
        } else {
            optiOrder = static_cast<int>(result);
            if (optiOrder > 0 && optiOrder <= nowFile->MaxOrder){
                nowFile->optiOrder = optiOrder;
                nowFile->meanOfOptiOrder = nowFile->fitError[optiOrder - 1] / nowFile->data.size();
                nowFile->varianceOfOptiOrder = calculateVariance(nowFile);
                displayInfo = true;
            }

        }
    }
}
void displayErrorChartProcessor() {
    if (nowFile->optiOrder != 0) {
        std::vector<std::vector<double>> data;
        for (int i = 0; i < nowFile->data.size(); ++i) {
            data.push_back({nowFile->data[i][0], nowFile->fitErrors[nowFile->optiOrder - 1][i]});
        }
        GuiLineChart *ErrorChart = new GuiLineChart(data, RED, 50, 10, 950, 300);
        nowScreen->labelVector.push_back(ErrorChart);
    }
}
