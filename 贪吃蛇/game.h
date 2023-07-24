#ifndef GAME_H
#define GAME_H

#include "stdbool.h"
#include "lcd.h"
#include "ts.h"

#define ROW 48
#define COL 80

#define EMPTY 0 // 标记空
#define WALL 1  // 标记墙
#define FOOD 2  // 标记食物
#define HEAD 3  // 标记蛇头
#define BODY 4  // 标记蛇身

struct Snake
{
    int len; // 蛇的的长度
    int x;   // 蛇头的X坐标
    int y;   // 蛇头的Y坐标
} snake;

struct Body
{
    int x;         // 蛇身横坐标
    int y;         // 蛇身纵坐标
} body[ROW * COL]; // 开辟足以存储蛇身的结构体数组

struct Food
{
    int x; // 食物横坐标
    int y; // 食物纵坐标
} food;

int grade; // 分数

int face[ROW][COL];

void game(); // 游戏主程序

bool clickSart(); // 开始

bool clicQuit(); // 结束

void InitFace(); // 初始化游戏界面

void randFood(); // 随机生成食物

void DrawSnake(); // 画蛇

void MoveSnake(int x, int y); // 移动蛇

#endif