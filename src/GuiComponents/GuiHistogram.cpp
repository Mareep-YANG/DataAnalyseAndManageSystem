//
// Created by ly on 2024/1/31.
//
#pragma once

#include <windef.h>
#include "GuiControllers.cpp"
#include "../Entities/FileEntity.cpp"
#include "graphics.h"
#include <iostream>
#include <sstream>
#include <cmath>
#include "GuiLabel.cpp"
class GuiHistogram : public GuiLabel {
public:
    std::vector<double> data ;
    int left;
    int top;
    int right;
    int bottom;
    float xscale,yscale;
    double max;
    int COLOR[16]={BLACK,BLUE,GREEN,CYAN,RED,MAGENTA,BROWN,LIGHTGRAY,DARKGRAY,LIGHTBLUE,LIGHTGREEN,LIGHTCYAN,LIGHTRED,LIGHTMAGENTA,YELLOW,WHITE};
    GuiHistogram(std::vector<double> data, int left, int top, int right, int bottom) {
        this->data = data;
        this->left = left;
        this->top = top;
        this->right = right;
        this->bottom = bottom;
        max=data[1];
        for(double d:data){
            this->max=std::max(d,max);
        }
        this->xscale=(this->right-this->left)/(float)this->data.size();
        this->yscale=(this->bottom-this->top)/(float)this->max;
    }


    void drawController() override {
        for(int i=0;i < data.size();i++)
        {
            setfillcolor(COLOR[i % 16]);
            solidrectangle(left+(i)*xscale,bottom-data[i]*yscale,left+(i+1)*xscale,bottom);
            // 绘制下标
            settextstyle(20, 0, _T("宋体"), 0, 0, 1000, false, false, false);
            settextcolor(BLACK); // 设置文本颜色
            outtextxy(left + i * xscale + 0.5 * xscale, bottom + 15, std::to_string(i+1).c_str()); // 在柱状图下方显示文本
            // 绘制数据值
            outtextxy(left + i * xscale ,bottom-data[i]*yscale-20,std::to_string(data[i]).c_str());
        }
    }
};