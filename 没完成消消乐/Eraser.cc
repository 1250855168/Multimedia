#include "Eraser.h"
#include "pthread.h"
#include <linux/input.h>
#include <thread>

Eraser::Eraser()
{
}

Eraser::~Eraser()
{
}

void Eraser::getCoordinate()
{

    x_read = -1;
    y_read = -1;

    // 1.打开触摸屏
    int touch_fd = open("/dev/input/event0", O_RDWR);
    ;

    struct input_event ts;
    // 一直读取
    while (1)
    {
        read(touch_fd, &ts, sizeof(ts));
        if (ts.type == EV_KEY && ts.code == BTN_TOUCH)
        {
            if (ts.value == 1)
            {
                printf("press\n");
            }
            else
            {
                printf("songkai\n");
            }
        }
        else if (ts.type == EV_ABS)
        {
            if (ts.code == ABS_X)
            {
                x_read = ts.value * 800 / 1024;
            }
            else if (ts.code == ABS_Y)
            {
                y_read = ts.value * 480 / 600;
            }
        }
        if (x_read >= 0 && y_read >= 0)
        {
            break;
        }
    }
    close(touch_fd);

    return;
}

void Eraser::InitGameMenu()
{
    l.Lcd_DisplayJPG(0, 0, (char *)"game.jpg");

    srand((unsigned)time(NULL)); // 随机种子

    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            blocks[i][j] = (rand() % 4 + 1);
        }
    }

    /*
        for (size_t i = 0; i < 80; i++)
        {
            block b;
            b.number = (rand() % 4 + 1);
            b.status = 0;
            B.push_back(b);
        }

        int x, y;
        x = 260;
        y = 400;
        int count = 0;
        for (block b : B)
        {
            if (b.number == 1)
            {
                l.Lcd_DisplayJPG(x, y, (char *)"1.jpg");
            }
            if (b.number == 2)
            {
                l.Lcd_DisplayJPG(x, y, (char *)"2.jpg");
            }
            if (b.number == 3)
            {
                l.Lcd_DisplayJPG(x, y, (char *)"3.jpg");
            }
            if (b.number == 4)
            {
                l.Lcd_DisplayJPG(x, y, (char *)"4.jpg");
            }
            y -= 51;
            count++;
            if (count == 8)
            {
                count = 0;
                printf("%d\n", count);
                y = 400;
                x += 51;
            }
        }
        */
}

int s_min, e_min;

int s_sec, e_sec;

void *timer(void *arg)
{
    // 开启定时器
    time_t timep;
    time(&timep);

    struct tm *p;
    p = gmtime(&timep);

    // 得到定时器的时间
    s_min = p->tm_min;
    printf("s_min=%d \n", s_min);

    s_sec = p->tm_sec;
    printf("s_sec=%d \n", s_sec);
    /*
        while (1)
        {
            if (e_min - s_min == 5 && s_sec - e_sec == 60)
            {
                break;
            }

            p = gmtime(&timep);

            e_min = p->tm_min;
            printf("e_min=%d \n", e_min);

            e_sec = p->tm_sec;
            printf("e_sec=%d \n", e_sec);
        }
        */
}
void Eraser::getsite()
{
    for (size_t i = 0; i < 8; i++)
    {
        if (y_read >= 400 - i * 50 && y_read <= 450 - i * 50)
        {
            m_y = i;
        }
    }
    for (size_t j = 0; j < 10; j++)
    {
        if (x_read >= 250 + j * 50 && x_read <= 300 + j * 50)
        {
            m_x = j;
        }
    }
}

bool get()
{
}

void Eraser::gaming()
{
    while (1)
    {
        l.Lcd_DisplayJPG(0, 0, (char *)"start.jpg");

        if (clickSart())
        {
            InitGameMenu(); // 初始化游戏数组

            drawMainMenu();

            // 开启定时器5min

            pthread_t t;

            pthread_create(&t, NULL, timer, NULL); // 对定时器开启一个线程

            pthread_detach(t);

            while (1)
            {

                eraser(); // 消除相同三个或以上的

                merger(); // 向下合并在一起

                drawMainMenu(); // 更新游戏界面

                getCoordinate();
                m_x1 = m_x;
                m_y1 = m_y;
                // 得到第一个坐标
                printf("x=%d \n", x_read);

                printf("y=%d \n", y_read);

                getsite(); // x1 y1 像素点坐标  x0 y0数组坐标

                printf("第一个坐标blocks[%d][%d] \n", m_x1, m_y1);

                if (m_x1 != -1 && m_y1 != -1)
                {
                    press1 = true;
                }

                // 第二个坐标

                while (1)
                {
                    getCoordinate();
                    m_x2 = m_x;
                    m_y2 = m_y;
                    // 得到第一个坐标
                    printf("x=%d \n", x_read);

                    printf("y=%d \n", y_read);

                    getsite(); // x1 y1 像素点坐标  x0 y0数组坐标

                    printf("第二个坐标blocks[%d][%d] \n", m_x2, m_y2);

                    if (m_x2 != -1 && m_y2 != -1)
                    {
                        press2 = true;
                        break;
                    }
                }

                if (press1 && press2)
                {
                    exchange(m_x1, m_y1, m_x2, m_y2);
                    press1 = press2 = false;
                }

                // ;

                // // 看是否可以进行消除
                // eraser();

                // 进行合并

                // 如果定时器时间到了 显示游戏分数 点击结束游戏  重新开始选择
                // }

                // if (DOWN == get_state(x0, y0))
                // {

                //     getsite(x0, y0); // x1 y1 像素点坐标  x0 y0数组坐标

                //     exchange(x0, y0, x1, y1);

                //     // 看是否可以进行消除
                //     eraser();

                //     // 进行合并

                //     // 如果定时器时间到了 显示游戏分数 点击结束游戏  重新开始选择
                // }

                // if (LEFT == get_state(x0, y0))
                // {

                //     getsite(x0, y0); // x1 y1 像素点坐标  x0 y0数组坐标

                //     exchange(x0, y0, x1, y1);

                //     // 看是否可以进行消除
                //     eraser();

                //     // 进行合并

                //     // 如果定时器时间到了 显示游戏分数 点击结束游戏  重新开始选择
                // }
                // if (RIGHT == get_state(x0, y0))
                // {

                //     getsite(x0, y0); // x1 y1 像素点坐标  x0 y0数组坐标

                //     exchange(x0, y0, x1, y1);

                //     // 看是否可以进行消除
                //     eraser();

                //     // 进行合并

                //     // 如果定时器时间到了 显示游戏分数 点击结束游戏  重新开始选择
                // }
            }
        }
        if (clicQuit())
        {
            break;
        }
    }
}

int Eraser::get_state(int *x, int *y)
{
    printf("Present Line: %d\n", __LINE__);     // 所在行
    printf("Present Function: %s\n", __func__); // 函数名
    int ts_fd = open("/dev/input/event0", O_RDWR);
    if (ts_fd == -1)
    {
        perror("");
    }
    lseek(ts_fd, 0, SEEK_SET);

    struct input_event ev;
    // 触摸第一次的坐标
    int x0 = -1, y0 = -1;
    int num = 0;
    // 实时坐标,最终为手最后一次离开触摸屏的
    while (1)
    {

        if (ev.type == EV_KEY && ev.code == 330 && ev.value == 1)
        {
            num = 0;
        }
        int n = read(ts_fd, &ev, sizeof(struct input_event));
        if (n != sizeof(struct input_event))
        {
            continue;
        }
        if (ev.type == EV_ABS && ev.code == ABS_X)
        {
            if (x0 == -1)
            {
                x0 = ev.value;
            }
            *x = ev.value;
        }
        if (ev.type == EV_ABS && ev.code == ABS_Y)
        {
            if (y0 == -1)
            {
                y0 = ev.value;
            }
            *y = ev.value;
        }
        if (ev.type == EV_KEY && ev.code == 330 && ev.value == 0)
        {
            printf("leave\n");
            break;
        }
        printf("Present Line: %d\n", __LINE__);     // 所在行
        printf("Present Function: %s\n", __func__); // 函数名
    }

    printf("Present Line: %d\n", __LINE__);     // 所在行
    printf("Present Function: %s\n", __func__); // 函数名

    x0 = x0 * 800 / 1024;
    *x = *x * 800 / 1024;
    y0 = y0 * 480 / 600;
    *y = *y * 480 / 600;
    printf("触摸开始坐标(%d , %d)\n", x0, y0);
    printf("触摸结束坐标(%d , %d)\n", *x, *y);

    // 根据斜率k获得方向值
    int k = abs((*y - y0) / (double)(*x - x0));
    // 上下方向
    if (k >= 1)
    {
        if (*y > y0)
        {
            printf("DOWN\n");
            return DOWN;
        }
        else if (*y < y0)
        {
            printf("UP\n");
            return UP;
        }
    }
    else
    {
        if (*x > x0)
        {
            printf("RIGHT\n");
            return RIGHT;
        }
        else if (*x < x0)
        {
            printf("LEFT\n");
            return LEFT;
        }
    }
}

void Eraser::merger()
{
    int x = 0;
    int y = 0;
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            if (blocks[i][j] != 0)
            {

                // 开辟新数组 接受
            }
        }
    }
}

bool Eraser::clickSart()
{
    getCoordinate(); // 得到X Y 对坐标
    if (x_read >= 205 && x_read <= 327 && y_read >= 130 && y_read <= 372)
    {
        return true;
    }
    return false;
}

bool Eraser::clicQuit()
{
    getCoordinate(); // 得到X Y 对坐标
    if (x_read >= 484 && x_read <= 628 && y_read >= 131 && y_read <= 376)
    {
        return true;
    }
    return false;
}

void Eraser::drawMainMenu()
{
    // 显示剩余时间
    // printf("min = %d \n", e_min - s_min);

    // printf("sec = %d \n", e_sec - s_sec);

    // 显示得分

    // 显示图片
    int x, y;
    x = 260;
    y = 400;
    int count = 0;
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            if (blocks[i][j] == 0)
            {
                blocks[i][j] = (rand() % 4 + 1);
            }

            if (blocks[i][j] == 1)
            {
                l.Lcd_DisplayJPG(x, y, (char *)"1.jpg");
            }
            if (blocks[i][j] == 2)
            {
                l.Lcd_DisplayJPG(x, y, (char *)"2.jpg");
            }
            if (blocks[i][j] == 3)
            {
                l.Lcd_DisplayJPG(x, y, (char *)"3.jpg");
            }
            if (blocks[i][j] == 4)
            {
                l.Lcd_DisplayJPG(x, y, (char *)"4.jpg");
            }
            y -= 51;
            count++;
            if (count == 8)
            {
                count = 0;
                y = 400;
                x += 51;
            }
        }
    }
}

bool Eraser::iscrossed(int x1, int y1, int x2, int y2, int x3, int y3)
{
    if (x1 < 0 || x1 >= 7 || y1 < 0 || y1 >= 9)
        return false;
    if (x2 < 0 || x2 >= 7 || y2 < 0 || y2 >= 9)
        return false;
    if (x3 < 0 || x3 >= 7 || y3 < 0 || y3 >= 9)
        return false;
    return true;
}

void Eraser::exchange(int x1, int y1, int x2, int y2)
{
    // 判断是否越界
    if (iscrossed(x1, y1, x2, y2, 1, 1))
    {
        // 相邻元素交换图片
        // 左元素
        if ((x1 - 1) >= 0 && blocks[x1 - 1][y1] == blocks[x2][y2])
        {

            int temp;
            temp = blocks[x1][y1];
            blocks[x1][y1] = blocks[x2][y2];
            blocks[x2][y2] = temp;
        }
        // 右边元素
        if ((x1 + 1) <= 7 && blocks[x1 + 1][y1] == blocks[x2][y2])
        {

            int temp;
            temp = blocks[x1][y1];
            blocks[x1][y1] = blocks[x2][y2];
            blocks[x2][y2] = temp;
        }

        // 上面元素
        if ((y1 - 1) >= 0 && blocks[x1][y1 - 1] == blocks[x2][y2])
        {

            int temp;
            temp = blocks[x1][y1];
            blocks[x1][y1] = blocks[x2][y2];
            blocks[x2][y2] = temp;
        }

        // 下面元素
        if ((y1 + 1) >= 9 && blocks[x1][y1 + 1] == blocks[x2][y2])
        {

            int temp;
            temp = blocks[x1][y1];
            blocks[x1][y1] = blocks[x2][y2];
            blocks[x2][y2] = temp;
        }

        // 进行交换
    }
}
// bool right(int x)
// {
//     if (x > 5)
//     {
//         return false;
//     }
//     return true;
// }

// bool down(int y)
// {
//     if (y > 6)
//     {
//         return false;
//     }
//     return true;
// }

// void setzero(int x, int y)
// {
// }

void Eraser::eraser()
{
    int count = 0;
    for (size_t i = 0; i < 8; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            if (blocks[i][j] == 1)
            {
                // 向右判断
                if (iscrossed(i, j, i + 1, j, i + 2, j) && blocks[i][j] == 1 && blocks[i + 1][j] == 1 && blocks[i + 2][j] == 1)
                {
                    for (size_t k = 3; k < 8; k++)
                    {
                        if (blocks[i + k][j] == 1)
                        {
                            blocks[i + k][j] == 0;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                // 向下判断
                if (iscrossed(i, j + 1, i, j + 1, i, j + 2) && blocks[i][j] == 1 && blocks[i][j + 1] == 1 && blocks[i][j + 2] == 1)
                {
                    for (size_t k = 3; k < 8; k++)
                    {
                        if (blocks[i][j + k] == 1)
                        {
                            blocks[i][j + k] == 0;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
            if (blocks[i][j] == 2)
            {
                // 向右判断
                if (iscrossed(i, j, i + 1, j, i + 2, j) && blocks[i][j] == 2 && blocks[i + 1][j] == 2 && blocks[i + 2][j] == 2)
                {
                    for (size_t k = 3; k < 8; k++)
                    {
                        if (blocks[i + k][j] == 1)
                        {
                            blocks[i + k][j] == 0;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                // 向下判断
                if (iscrossed(i, j + 1, i, j + 1, i, j + 2) && blocks[i][j] == 2 && blocks[i][j + 1] == 2 && blocks[i][j + 2] == 2)
                {
                    for (size_t k = 3; k < 8; k++)
                    {
                        if (blocks[i][j + k] == 1)
                        {
                            blocks[i][j + k] == 0;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
            if (blocks[i][j] == 3)
            {
                // 向右判断
                if (iscrossed(i, j, i + 1, j, i + 2, j) && blocks[i][j] == 3 && blocks[i + 1][j] == 3 && blocks[i + 2][j] == 3)
                {
                    for (size_t k = 3; k < 8; k++)
                    {
                        if (blocks[i + k][j] == 1)
                        {
                            blocks[i + k][j] == 0;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                // 向下判断
                if (iscrossed(i, j + 1, i, j + 1, i, j + 2) && blocks[i][j] == 3 && blocks[i][j + 1] == 3 && blocks[i][j + 2] == 3)
                {
                    for (size_t k = 3; k < 8; k++)
                    {
                        if (blocks[i][j + k] == 1)
                        {
                            blocks[i][j + k] == 0;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
            if (blocks[i][j] == 4)
            {
                // 向右判断
                if (iscrossed(i, j, i + 1, j, i + 2, j) && blocks[i][j] == 4 && blocks[i + 1][j] == 4 && blocks[i + 2][j] == 4)
                {
                    for (size_t k = 3; k < 8; k++)
                    {
                        if (blocks[i + k][j] == 1)
                        {
                            blocks[i + k][j] == 0;
                        }
                        else
                        {
                            break;
                        }
                    }
                }

                // 向下判断
                if (iscrossed(i, j + 1, i, j + 1, i, j + 2) && blocks[i][j] == 4 && blocks[i][j + 1] == 4 && blocks[i][j + 2] == 4)
                {
                    for (size_t k = 3; k < 8; k++)
                    {
                        if (blocks[i][j + k] == 1)
                        {
                            blocks[i][j + k] == 0;
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
        }
    }
}