//
// Created by ly on 2024/1/31.
//
#pragma once

#include <windef.h>
#include "GuiControllers.cpp"
#include "../Entities/FileEntity.cpp"
#include "graphics.h"
#include <iostream>
#include "GuiLabel.cpp"
class GuiLineChart : public GuiLabel {
public:
    std::vector<std::vector<double>> data ;
    COLORREF color;
    int left;
    int top;
    int right;
    int bottom;
    double minX , scaleX, minY , scaleY, maxX , maxY,height,width;
    GuiLineChart(std::vector<std::vector<double>> data, COLORREF color, int left, int top, int right, int bottom) {
        this->data = data;
        this->color = color;
        this->left = left;
        this->top = top;
        this->right = right;
        this->bottom = bottom;
        minX = data[0][0]; minY = data[0][1] ; maxX = data[0][0];maxY = data[0][1];
        for (std::vector<double> v: data) {
            this->minX = std::min(minX, v[0]);
            this->minY = std::min(minY, v[1]);
            this->maxX = std::max(maxX, v[0]);
            this->maxY = std::max(maxY, v[1]);
        }
        this->scaleX = this->maxX - this->minX;
        this->scaleY = this->maxY - this->minY;
        height = this->bottom - this->top;
        width = this->right - this->left;
    }

    void drawController() override {
        // Plot the graph
        setlinecolor(color);
        setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 2);
        for (int i = 0; i < data.size() - 1; i++) {
            line(left + (data[i][0] - minX) / scaleX * width,
                 bottom - (data[i][1] - minY) / scaleY * height,
                 left + (data[i + 1][0] - minX) / scaleX * width,
                 bottom - (data[i + 1][1] - minY) / scaleY * height);
        }
    }

};