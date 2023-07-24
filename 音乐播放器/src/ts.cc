#include "ts.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <new>

ts *ts::g_pSingleton = new (std::nothrow) ts();

ts *ts::GetInstance()
{
    return g_pSingleton;
}

void ts::deleteInstance()
{
    if (g_pSingleton)
    {
        delete g_pSingleton;
        g_pSingleton = nullptr;
    }
}

int ts::open_ts()
{
    ts_fd = open("/dev/input/event0", O_RDWR | O_NONBLOCK);
    if (ts_fd < 0)
    {
        perror("open /dev/input/event0 failed");
        return -1;
    }
    return 0;
}

int ts::close_ts()
{
    int ret = close(ts_fd);
    if (ret < 0)
    {
        perror("close /dev/input/event0 failed");
        return -1;
    }
    return 0;
}

void ts::get_dir()
{
    struct input_event ev;

    while (1)
    {
        while (1)
        {
            lseek(ts_fd, 0, SEEK_SET);

            m_x1 = -1;
            m_y1 = -1;

            while (1)
            {

                if (ev.type == EV_KEY && ev.code == 330 && ev.value == 1)
                {
                    num = 0; // 第一次进入的num的值
                }
                num++; // 用它判断压力值
                int n = read(ts_fd, &ev, sizeof(struct input_event));
                if (n != sizeof(struct input_event))
                {
                    continue; // 如果大小不等于这个结构体 读取失败 重新读
                }
                if (ev.type == EV_ABS && ev.code == ABS_X)
                {
                    if (m_x1 == -1)
                    {
                        m_x1 = ev.value; // 得到X的按压的起始位置的坐标
                    }
                    m_x2 = ev.value; // 得到X的按压的结束位置的坐标
                }
                if (ev.type == EV_ABS && ev.code == ABS_Y)
                {
                    if (m_y1 == -1)
                    {
                        m_y1 = ev.value; // 得到Y的按压的起始位置的坐标
                    }
                    m_y2 = ev.value; // 得到Y的按压的结束位置的坐标
                }
                if (ev.type == EV_KEY && ev.code == 330 && ev.value == 0)
                {
                    break; // 按压结束 跳出循环
                }
            }

            // 给屏幕的坐标进行转换 800-480
            m_x1 = m_x1 * 800 / 1024;
            m_x2 = m_x2 * 800 / 1024;
            m_y1 = m_y1 * 480 / 600;
            m_y2 = m_y2 * 480 / 600;

            printf("m_x1 = %d m_y1 = %d\n", m_x1, m_y1);
            printf("m_x2 = %d m_y2 = %d\n", m_x2, m_y2);

            if (m_x1 == m_x2 && m_y1 == m_y2)
            {
                if (num > 500000)
                {
                    m_dir = PRESS;
                    break;
                }
                break;
            }
            int k = abs((m_y2 - m_y1) / (double)(m_x2 - m_x1));
            // 上下方向
            if (k >= 1)
            {
                if (m_y2 > m_y1)
                {
                    m_dir = DOWN;
                    printf("DOWN\n");
                    break;
                }
                else if (m_y2 < m_y1)
                {
                    m_dir = UP;
                    printf("UP\n");
                    break;
                }
            }
            else
            {
                if (m_x2 > m_x1)
                {
                    m_dir = RIGHT;
                    printf("RIGHT\n");
                    break;
                }
                else if (m_x2 < m_x1)
                {
                    m_dir = LEFT;
                    printf("LEFT\n");
                    break;
                }
            }
        }
    }
    return;
}

int ts::g_dir() // 得到方向
{
    return this->m_dir;
}

int ts::g_x() // 得到X的坐标
{
    return this->m_x2;
}

int ts::g_y() // 得到Y的坐标
{
    return this->m_y2;
}

void ts::set_dir(int x)
{
    this->m_dir = x;
}