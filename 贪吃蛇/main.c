#include "word.h"
#include "ts.h"
#include "game.h"
#include <pthread.h>

int main(int argc, char **argv)
{
    Lcd_Init(); // 屏幕初始化

    srandom(time(NULL)); // 设置随机数的种子

    open_ts(); // 打开触摸屏

    pthread_t tid;
    pthread_create(&tid, NULL, getDir, NULL);

    game();

    pthread_detach(tid);

    close_ts(); // 关闭触摸屏

    Lcd_Uinit(); // 关闭屏幕
}
