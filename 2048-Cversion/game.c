#include "game.h"
#include "input.h"
#include "output.h"
#include<time.h>
#include<stdlib.h>
#include <stdio.h>
#define ROW 4
#define COL 4

static int array[ROW][COL] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};
static int temp[ROW][COL] = {
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};

static int sum=0;

// 在随机的位置生成一个随机的数字
void get_randnumber()
{
    int i;
    int j;
    srand((unsigned)time(NULL)); //使用随机函数
    do
    {
        i = rand() % 4; //获得随机值下标
        j = rand() % 4;
    } while (array[i][j] != 0);
    array[i][j] = Get_2_4(); //把随机值赋给数组
}

// 游戏初始化
void game_init()
{
    // 在随机的位置生成一个随机的数字
    get_randnumber();
    // 在随机的位置生成一个随机的数字
    get_randnumber();
    // 显示界面
    show_ui(array, ROW, COL,sum);
}
// 游戏主循环
void game_run()
{
    while (1)
    {
        // 获取一个方向
        Direction d = get_direction();
        // 根据用户输入的方向，操作二维数组
        switch (d)
        {
        case LEFT:
            move_left();
            break;
        case RIGHT:
            move_right();
            break;
        case UP:
            move_up();
            break;
        case DOWN:
            move_down();
            break;
        default:
            break;
        }
        show_ui(array, ROW, COL,sum);
        Is_game_close();
    }
}

/*
2 2 2 2 =>  4 4 0 0
2 0 2 0 =>  4 0 0 0
2 0 0 2 =>  4 0 0 0
0 0 0 2 =>  2 0 0 0

int b[4] = {2, 2, 2, 2}; => {4, 0, 4, 0}

*/

void move_left()
{
    //拷贝原来数组
    copy_origin_array();
    // 压缩
    compress_left();
    // 合并
    merge_left();
    // 压缩
    compress_left();
    //判断是否为需要添加新数字
    get_number();
}

void merge_left()
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL - 1; j++)
        {
            if (array[i][j] == array[i][j + 1])
            {
                array[i][j] *= 2;
                sum+=array[i][j + 1];
                array[i][j + 1] = 0;
            }
        }
    }
}

void compress_left()
{
    for (int i = 0; i < ROW; i++)
    {
        int tmp[COL] = {0};
        int k = 0;
        // 如果该行的元素的值非0，写入到tmp数组
        for (int j = 0; j < COL; j++)
        {
            if (array[i][j] != 0)
            {
                tmp[k++] = array[i][j];
            }
        }
        // 把tmp数组的值覆盖掉二维数组对应的行
        for (int j = 0; j < COL; j++)
        {
            array[i][j] = tmp[j];
        }
    }
}

void move_right()
{
    //拷贝原来数组
    copy_origin_array();
    // 压缩
    compress_right();
    // 合并
    merge_right();
    // 压缩
    compress_right();
    //判断是否为需要添加新数字
    get_number();
}

void compress_right()
{
    for (int i = 0; i < ROW; i++)
    {
        int tmp[COL] = {0};
        int k = COL - 1;
        // 如果该行的元素的值非0，写入到tmp数组
        for (int j = COL - 1; 0 <= j; j--)
        {
            if (array[i][j] != 0)
            {
                tmp[k--] = array[i][j];
            }
        }
        // 把tmp数组的值覆盖掉二维数组对应的行
        for (int j = 0; j < COL; j++)
        {
            array[i][j] = tmp[j];
        }
    }
}

void merge_right()
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = COL - 1; j > 0; j--)
        {
            if (array[i][j] == array[i][j - 1])
            {
                array[i][j] *= 2;
                sum+=array[i][j - 1];
                array[i][j - 1] = 0;
            }
        }
    }
}

void move_up()
{
    //拷贝原来数组
    copy_origin_array();
    // 压缩
    compress_up();
    // 合并
    merge_up();
    // 压缩
    compress_up();
    //判断是否为需要添加新数字
    get_number();
}

void compress_up()
{
    for (int i = 0; i < ROW; i++)
    {
        int tmp[COL] = {0};
        int k = 0;
        // 如果该行的元素的值非0，写入到tmp数组
        for (int j = 0; j < COL; j++)
        {
            if (array[j][i] != 0)
            {
                tmp[k++] = array[i][j];
            }
        }
        // 把tmp数组的值覆盖掉二维数组对应的行
        for (int j = 0; j < COL; j++)
        {
            array[j][i] = tmp[j];
        }
    }
}

void merge_up()
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL - 1; j++)
        {
            if (array[j][i] == array[j + 1][i])
            {
                array[j][i] *= 2;
                sum+=array[j + 1][i];
                array[j + 1][i] = 0;
            }
        }
    }
}

void move_down()
{
    //拷贝原来数组
    copy_origin_array();
    // 压缩
    compress_down();
    // 合并
    merge_down();
    // 压缩
    compress_down();
    //判断是否为需要添加新数字
    get_number();
}

void compress_down()
{
    for (int i = 0; i < ROW; i++)
    {
        int tmp[COL] = {0};
        int k = COL - 1;
        // 如果该行的元素的值非0，写入到tmp数组
        for (int j = COL - 1; 0 <= j; j--)
        {
            if (array[j][i] != 0)
            {
                tmp[k--] = array[j][i];
            }
        }
        // 把tmp数组的值覆盖掉二维数组对应的行
        for (int j = 0; j < COL; j++)
        {
            array[j][i] = tmp[j];
        }
    }
}

void merge_down()
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = COL - 1; j > 0; j--)
        {
            if (array[j][i] == array[j - 1][i])
            {
                array[j][i] *= 2;
                sum+=array[j - 1][i];
                array[j - 1][i] = 0;
            }
        }
    }
}

void copy_origin_array() //拷贝原来数组
{
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            temp[i][j] = array[i][j];
        }
    }
}

int Is_effect_change() //把原来数组和当前数组进行判断
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (temp[i][j] != array[i][j])
            {
                return 1;
            }
        }
    }
    return 0;
}

int Get_2_4()
{
    int b[4] = {2, 2, 2, 4};
    srand((unsigned)time(NULL));
    int i = rand() % 4;
    return b[i]; //得到一个数字 2的几率为75% 4为25%
}
void add_number()
{
    int i;
    int j;
    srand((unsigned)time(NULL)); //把这个新数加入到数组里面

    do
    {
        i = rand() % 4;
        j = rand() % 4;
    } while (array[i][j] != 0);
    array[i][j] = Get_2_4();
}

void get_number()
{
    if (Is_effect_change()) //如果是有效改变随机添加一个新数字
    {
        add_number();
    }
}

int Is_game_close() //判断游戏结束 获得胜利 还是继续游戏
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if ((array[i][j] == 2048)) //相邻能相等 有0 游戏继续
            {
                printf("恭喜你获得胜利！");
                return 1;
            }
        }
    }

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if ((array[i][j] == 0) || (array[i][j] == array[i + 1][j]) || array[i][j] == array[i][j + 1]) //相邻能相等 有0 游戏继续
            {
                return 0;
            }
        }
    }
    return 1; //游戏结束
}
