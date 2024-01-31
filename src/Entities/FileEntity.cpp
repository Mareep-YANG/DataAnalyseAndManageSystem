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
    double polyCoeff[20][20];;// �洢ÿ�׵Ķ���ʽϵ��
    std::vector<double> fitError;// �洢ÿ�׵���������
    std::vector<std::vector<double>> fitErrors;// �洢ÿ�׵�������
    std::vector<std::vector<double>> fity;// �洢ÿ�׵���Ϻ���ֵ
    int optiOrder;// ���Ž���
    float meanOfOptiOrder;// ���Ž������������ֵ
    float varianceOfOptiOrder;// ���Ž������������
    FileEntity(std::string filename,std::vector<std::vector<double>> data){
        this->filename = filename;
        this->data = data;
    }
};
