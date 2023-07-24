#include "game.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

bool clickSart()
{
    // int x_read = 0;
    // int y_read = 0;
    // get_state(&x_read, &y_read);
    // if (x_read >= 205 && x_read <= 327 && y_read >= 130 && y_read <= 372)
    // {
    //     return true;
    // }
    // return false;

    return true;
}

bool clicQuit()
{
    // int x_read = 0;
    // int y_read = 0;
    // get_state(&x_read, &y_read);
    // if (x_read >= 484 && x_read <= 628 && y_read >= 131 && y_read <= 376)
    // {
    //     return true;
    // }
    // return false;

    return true;
}

void InitFace()
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (j == 0 || j == COL - 1)
            {
                face[i][j] = WALL; // 标记该位置为墙
            }
            else if (i == 0 || i == ROW - 1)
            {
                face[i][j] = WALL; // 标记该位置为墙
            }
            else
            {
                face[i][j] = EMPTY; // 标记该位置为空
            }
        }
    }
}

void show()
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            printf("%d ", face[i][j]);
        }
        printf("\n");
    }
}

void InitSnake()
{
    snake.len = 2;     // 蛇的身体长度初始化为2
    snake.x = ROW / 2; // 蛇头位置的横坐标
    snake.y = COL / 2; // 蛇头位置的纵坐标
    // 蛇身坐标的初始化
    body[0].x = COL / 2 - 1;
    body[0].y = ROW / 2;
    body[1].x = COL / 2 - 2;
    body[1].y = ROW / 2;
    // 将蛇头和蛇身位置进行标记
    // face[snake.x][snake.y] = HEAD;
    face[body[0].y][body[0].x] = BODY;
    face[body[1].y][body[1].x] = BODY;

    grade = 0;
}

void randFood()
{
    do
    {
        // 随机生成食物的横纵坐标
        food.x = rand() % ROW;
        food.y = rand() % COL;
    } while (face[food.x][food.y] != EMPTY); // 确保生成食物的位置为空，若不为空则重新生成
    face[food.x][food.y] = FOOD;             // 将食物位置进行标记
}

void DrawSnake()
{
    // // 打印蛇头
    // Lcd_DisplayJPG(snake.y * 10, snake.x * 10, (char *)"head.jpg");

    // for (int i = 0; i < snake.len; i++)
    // {
    //     // 打印蛇身
    //     Lcd_DisplayJPG(body[i].x * 10, body[i].y * 10, (char *)"head.jpg");
    // }

    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (face[i][j] == BODY) // 打印蛇身
            {
                Lcd_DisplayJPG(j * 10, i * 10, (char *)"body.jpg");
            }
            else if (face[i][j] == HEAD) // 打印蛇头
            {
                Lcd_DisplayJPG(j * 10, i * 10, (char *)"head.jpg");
            }
            else if (face[i][j] == EMPTY)
            {
                Lcd_DisplayJPG(j * 10, i * 10, (char *)"background.jpg"); // 标记该位置为空
            }
            else if (face[i][j] == FOOD)
            {
                Lcd_DisplayJPG(j * 10, i * 10, (char *)"food.jpg");
            }
            else
            {
                Lcd_DisplayJPG(j * 10, i * 10, (char *)"wall.jpg");
            }
        }
    }
}

void JudgeFunc(int x, int y)
{
    // 若蛇头即将到达的位置是食物，则得分
    if (face[body[0].y + y][body[0].x + x] == FOOD)
    {
        face[food.x][food.y] = EMPTY;
        snake.len++;
        randFood();

        grade *= 10;
    }
    // 若蛇头即将到达的位置是墙或者蛇身，则游戏结束
    else if (face[body[0].y + y][body[0].x + x] == WALL || face[body[0].y + y][body[0].x + x] == BODY)
    {
        sleep(1000); // 留给玩家反应时间
        while (1)    // 询问玩家是否再来一局
        {
        }
    }
}

void MoveSnake(int x, int y)
{
    JudgeFunc(x, y); // 游戏判断

    // 向一个方向移动
    face[body[snake.len - 1].y][body[snake.len - 1].x] = EMPTY;
    for (int i = snake.len - 1; i > 0; i--)
    {
        body[i].x = body[i - 1].x;
        body[i].y = body[i - 1].y;
    }

    body[0].x += x;
    body[0].y += y;

    for (int i = snake.len - 1; i >= 0; i--)
    {
        face[body[i].y][body[i].x] = BODY;
    }
}

void game()
{

    Lcd_DisplayJPG(0, 0, (char *)"start.jpg"); // 初始化开始界面

    while (1)
    {
        if (clickSart())
        {

            InitFace();

            InitSnake();

            Lcd_DisplayJPG(0, 0, (char *)"game.jpg"); // 初始化游戏界面

            randFood();

            show();

            DrawSnake();

            Dir = RIGHT;

            int tempDir = -1;

            tempDir = Dir;

            while (1)
            {
                DrawSnake();

                printf("Dir = %d\n", Dir);

                switch (Dir)
                {
                case UP:
                    if (tempDir != DOWN)
                    {
                        tempDir = Dir;
                        MoveSnake(0, -1);
                    }
                    else
                    {
                        Dir = tempDir;
                    }
                    break;

                case DOWN:
                    if (tempDir != UP)
                    {
                        tempDir = Dir;
                        MoveSnake(0, 1);
                    }
                    else
                    {
                        Dir = tempDir;
                    }
                    break;

                case LEFT:
                    if (tempDir != RIGHT)
                    {
                        tempDir = Dir;
                        MoveSnake(-1, 0);
                    }
                    else
                    {
                        Dir = tempDir;
                    }
                    break;

                case RIGHT:
                    if (tempDir != LEFT)
                    {
                        tempDir = Dir;
                        MoveSnake(1, 0);
                    }
                    else
                    {
                        Dir = tempDir;
                    }
                    break;

                default:
                    break;
                }
                // 得到方向

                // 吃食物

                usleep(100000 / 4);
            }
        }
    }
    if (clicQuit())
    {
        // 退出游戏
    }
}
