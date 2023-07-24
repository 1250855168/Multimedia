// #include "DCList.h"
#include "lcd.h"
#include "ts.h"
#include "madplay.h"
#include "mplayer.h"

#include <iostream>
#include <thread>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <sys/wait.h>

int main()
{

    // 保证线程安全我们使用单列模式

    lcd::GetInstance()->Lcd_Init();

    ts::GetInstance()->open_ts();

    std::thread t1(&ts::get_dir, ts::GetInstance());

    t1.detach();

    while (1)
    {
        // 进行选择图片
        //   lcd::GetInstance()->Lcd_DisplayJPG(0, 0, (char *)"select.jpg");

        // 如果选择MP3
        // madplay::GetInstance()->music_play(); // 父子进程交互数据 播放MP3
        // 打开MP3页面
        //   lcd::GetInstance()->Lcd_DisplayJPG(0, 0, (char *)"mp3.jpg");

        // 如果选择MP4
        mplayer::GetInstance()->video_play(); // 父子进程交互数据 播放MP4
        // 打开MP3页面
        //  lcd::GetInstance()->Lcd_DisplayJPG(0, 0, (char *)"mp4.jpg");
    }

    // 关闭资源

    lcd::GetInstance()->Lcd_Uinit();

    lcd::deleteInstance();

    ts::GetInstance()->close_ts();

    ts::deleteInstance();

    // madplay::deleteInstance();

    mplayer::deleteInstance();

    return 0;
}