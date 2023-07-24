
#pragma once

#define PRESS 0
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

class ts
{
private:
    int ts_fd;         // 触摸的文件描述符
    int m_dir;         // 获得方向
    int m_click_press; // 判断是点击还是按压
    int m_x1;          // 按压点起始的X的坐标
    int m_y1;          // 按压点起始的Y的坐标
    int m_x2;          // 按压点结束的X的坐标
    int m_y2;          // 按压点结束的Y的坐标
    int num;           // 判断压力值

    // 将其构造和析构成为私有的, 禁止外部构造和析构
    ts() = default;
    ~ts() = default;

    // 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
    ts(const ts &l);
    const ts &operator=(const ts &l);

    // 唯一单实例对象指针
    static ts *g_pSingleton;

public:
    int open_ts();

    void get_dir(); // 循环方向

    int close_ts();

    int g_dir(); // 得到方向值

    void set_dir(int x);

    int g_x(); // 得到X的坐标

    int g_y(); // 得到Y的坐标

    // 获取单实例
    static ts *GetInstance();

    // 释放单实例，进程退出时调用
    static void deleteInstance();
};
