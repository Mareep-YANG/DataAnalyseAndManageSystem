//
// Created by ly on 2024/1/30.
//
#pragma once
#include <string>

class SavedDataEntity{
public:
    std::string filename;
    int optiOrder;// 最优阶数
    float meanOfOptiOrder;// 最优阶数的拟合误差均值
    float varianceOfOptiOrder;// 最优阶数的拟合误差方差
    SavedDataEntity(std::string filename,int optiOrder, float meanOfOptiOrder,float varianceOfOptiOrder){
        this->filename = filename;
        this->optiOrder = optiOrder;
        this->meanOfOptiOrder = meanOfOptiOrder;
        this->varianceOfOptiOrder = varianceOfOptiOrder;
    }
};
