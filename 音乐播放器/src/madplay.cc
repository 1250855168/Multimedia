#include "madplay.h"
#include "ts.h"
#include "lcd.h"
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
#include "DCList.h"

madplay *madplay::g_pSingleton = new (std::nothrow) madplay();

madplay *madplay::GetInstance()
{
    return g_pSingleton;
}

void madplay::deleteInstance()
{
    if (g_pSingleton)
    {
        delete g_pSingleton;
        g_pSingleton = nullptr;
    }
}

int madplay::get_status()
{
    status = -1;

    if (ts::GetInstance()->g_dir() == UP)
    {
        status = QUIT;
    }
    else if (ts::GetInstance()->g_dir() == DOWN)
    {
        status = STOP;
    }
    else if (ts::GetInstance()->g_dir() == LEFT)
    {
        status = PRE;
    }
    else if (ts::GetInstance()->g_dir() == RIGHT)
    {
        status = NEXT;
    }
    ts::GetInstance()->set_dir(-1);

    return status;
}

int madplay::music_play()
{
    int flag = -1;
    struct dirent *mydir;
    DCList d;
    std::shared_ptr<DCList::Node> list;
    DIR *dir = NULL;
    dir = opendir(PATHNAMEMP3);
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
            if (mydir->d_name[i] == '.' && mydir->d_name[i + 1] == 'm' && mydir->d_name[i + 2] == 'p' && mydir->d_name[i + 3] == '3')
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

    printf("成功打开音乐播放器！\n");

    mkfifo("fifo_cmd", 0666);

    pid_t pid = fork();

    if (pid == 0) // 子进程
    {
        bzero(buf, 20);
        sprintf(buf, "%s/%s", PATHNAMEMP3, head->data);
        // 启动mplayer
        execlp("mplayer",
               "mplayer", "-slave", "-quiet", "-idle",
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

            madplay::get_status();
            printf("%d\n", status);

            // 下一首
            if (status == NEXT)
            {
                printf("%d\n", status);
                status = -1;
                head = head->next;
                bzero(buf, 20);
                sprintf(buf, "loadfile %s/%s \n", PATHNAMEMP3, head->data);
                write(fd, buf, strlen(buf));
            }

            // 上一首
            if (status == PRE)
            {
                printf("%d\n", status);
                status = -1;
                head = head->prev;
                bzero(buf, 20);
                sprintf(buf, "loadfile %s/%s \n", PATHNAMEMP3, head->data);
                write(fd, buf, strlen(buf));
            }

            // 暂停
            if (status == STOP)
            {
                status = -1;
                write(fd, "pause\n", strlen("pause\n"));
            }

            sleep(1);
        }

        wait(NULL);

        close(fd);
    }
}