#include "mplayer.h"
#include "ts.h"
#include "lcd.h"
#include "DCList.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <new>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>

mplayer *mplayer::g_pSingleton = new (std::nothrow) mplayer();

mplayer *mplayer::GetInstance()
{
    return g_pSingleton;
}

void mplayer::deleteInstance()
{
    if (g_pSingleton)
    {
        delete g_pSingleton;
        g_pSingleton = nullptr;
    }
}

int mplayer::get_status()
{
    status = ts::GetInstance()->g_dir();

    if (status == UP)
    {
        status = ADDSOUND;

        ts::GetInstance()->set_dir(-1);
        printf("%d\n", status);

        return status;
    }
    else if (status == DOWN)
    {
        status = DISSOUND;

        ts::GetInstance()->set_dir(-1);
        printf("%d\n", status);

        return status;
    }
    else if (status == LEFT)
    {
        status = PRE;

        ts::GetInstance()->set_dir(-1);
        printf("%d\n", status);

        return status;
    }
    else if (status == RIGHT)
    {
        status = NEXT;

        ts::GetInstance()->set_dir(-1);
        printf("%d\n", status);

        return status;
    }
    else if (status == PRESS)
    {
        status = STOP;

        ts::GetInstance()->set_dir(-1);
        printf("%d\n", status);

        return status;
    }

    return status;
}

int mplayer::video_play()
{
    int flag = -1;
    struct dirent *mydir;
    DCList d;
    std::shared_ptr<DCList::Node> list;
    DIR *dir = NULL;
    dir = opendir(PATHNAMEMP4);
    if (dir == NULL)
    {
        perror("opendir");
        return 0;
    }
    // mydir = readdir(dir);

    while ((mydir = readdir(dir)) != NULL)
    {
        if (!strcmp(mydir->d_name, ".") || !strcmp(mydir->d_name, ".."))
        {
            continue; // 逃过隐藏的 .和 ..目录
        }
        for (int i = 0; i < strlen(mydir->d_name); i++)
        {
            if (mydir->d_name[i] == '.' && mydir->d_name[i + 1] == 'm' && mydir->d_name[i + 2] == 'p' && mydir->d_name[i + 3] == '4')
            {
                if (flag == -1)
                {
                    list = d.list_init((char *)mydir->d_name); // 初始化双向循环链表
                    flag++;
                }
                else
                {
                    std::shared_ptr<DCList::Node> node = d.newnode(mydir->d_name); // 创建新节点
                    d.addnode(move(node), list);                                   // 插入新节点
                }
                break;
            }
        }
    }
    closedir(dir);

    char buf[20]; // 用于存放拼接后的字符串
    std::shared_ptr<DCList::Node> head = list;

    printf("%s\n", head->data);

    printf("%s\n", head->next->data);

    printf("%s\n", head->next->next->data);

    printf("%s\n", head->next->next->next->data);

    printf("成功打开视频播放器！\n");

    mkfifo("fifo_cmd", 0666);

    pid_t pid = fork();

    if (pid == 0) // 子进程
    {
        bzero(buf, 20);
        sprintf(buf, "%s/%s", PATHNAMEMP4, head->data);
        // 启动mplayer
        execlp("mplayer", "mplayer",
               "-slave", "-quiet", "-vf",
               "scale=800:480",
               "-input", "file=./fifo_cmd",
               buf, NULL);
    }
    else if (pid > 0) // 父进程
    {
        // 以写的方式打开命名管道 fifo_cmd
        int fd = open("fifo_cmd", O_WRONLY);
        if (fd < 0)
        {
            perror("open");
        }

        while (1)
        {
            get_status();

            // 下一首
            if (status == NEXT)
            {
                head = head->next;
                bzero(buf, 20);
                sprintf(buf, "loadfile  %s/%s \n", PATHNAMEMP4, head->data);
                write(fd, buf, strlen(buf));
            }
            else if (status == PRE) // 上一首
            {
                head = head->prev;
                bzero(buf, 20);
                sprintf(buf, "loadfile  %s/%s \n", PATHNAMEMP4, head->data);
                write(fd, buf, strlen(buf));
            }
            else if (status == STOP) // 暂停
            {
                write(fd, "pause\n", strlen("pause\n"));
            }
            else if (status == DISSOUND)
            {
                printf("%d\n", status);
                write(fd, "seek +5\n", strlen("seek +5\n"));
            }
            else if (status == ADDSOUND)
            {
                printf("%d\n", status);
                write(fd, "seek -5\n", strlen("seek -5\n"));
            }
        }

        wait(NULL);

        close(fd);
    }
}