//
// Created by ly on 2024/1/30.
//
#pragma once
#include <string>

class SavedDataEntity{
public:
    std::string filename;
    int optiOrder;// ���Ž���
    float meanOfOptiOrder;// ���Ž������������ֵ
    float varianceOfOptiOrder;// ���Ž������������
    SavedDataEntity(std::string filename,int optiOrder, float meanOfOptiOrder,float varianceOfOptiOrder){
        this->filename = filename;
        this->optiOrder = optiOrder;
        this->meanOfOptiOrder = meanOfOptiOrder;
        this->varianceOfOptiOrder = varianceOfOptiOrder;
    }
};
