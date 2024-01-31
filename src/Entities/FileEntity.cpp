//
// Created by ly on 2024/1/30.
//
#pragma once
#include <vector>
#include <string>

class FileEntity{
public:
    int MaxOrder;
    std::string filename;
    std::vector<std::vector<double>> data ;
    double polyCoeff[20][20];;// 存储每阶的多项式系数
    std::vector<double> fitError;// 存储每阶的总拟合误差
    std::vector<std::vector<double>> fitErrors;// 存储每阶的拟合误差
    std::vector<std::vector<double>> fity;// 存储每阶的拟合函数值
    int optiOrder;// 最优阶数
    float meanOfOptiOrder;// 最优阶数的拟合误差均值
    float varianceOfOptiOrder;// 最优阶数的拟合误差方差
    FileEntity(std::string filename,std::vector<std::vector<double>> data){
        this->filename = filename;
        this->data = data;
    }
};
