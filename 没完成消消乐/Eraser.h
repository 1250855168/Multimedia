#pragma once

using namespace std;

#include "Lcd.h"
#include <memory>
#include <iostream>
#include <vector>
#include <condition_variable>
#include <cmath>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

class Eraser
{
private:
    struct block
    {
        char number;
        bool status;
    };

    int blocks[8][10];

    int t_blocks[8][10];

    Lcd l;

    vector<block> B;

    condition_variable start;

    int x_read; // lcd屏幕x的坐标

    int y_read; // lcd屏幕y的坐标

    int m_x; // 数组坐标 X
    int m_y; // 数组坐标 Y

    bool press1; // 第一个坐标按下

    bool press2; // 第一个坐标按下

    bool press;

    int m_x1;//第一次X的坐标

    int m_x2;//第二次X的坐标

    int m_y1;//第一次Y的坐标

    int m_y2;//第二次Y的坐标

public:
    Eraser(); // 无参构造函数

    void InitGameMenu(); // 初始化游戏界面

    void getCoordinate(); // 得到坐标

    bool clickSart(); // 点击开始游戏

    bool clicQuit(); // 点击退出游戏

    void drawMainMenu(); // 绘制主要的游戏界面

    void gaming(); // 游戏主界面 主线程

    void exchange(int x1, int y1, int x2, int y2); // 交换图面 线程0

    void score(); // 游戏得分  线程1

    bool iscrossed(int x1, int y1, int x2, int y2, int x3, int y3); // 判断是否越界

    void getsite();

    void eraser(); // 进行消除

    void merger(); // 进行合并

    int get_state(int *x, int *y);

    ~Eraser();
};
