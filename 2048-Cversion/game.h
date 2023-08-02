#ifndef GAME_H_
#define GAME_H_

// 游戏初始化
void game_init();
// 游戏主循环
void game_run();
// 释放游戏资源
void game_close();

// 合并
void merge_left();
// 压缩
void compress_left();
//向左移动
void move_left();

// 合并
void merge_right();
// 压缩
void compress_right();
//向左移动
void move_right();

// 合并
void merge_up();
// 压缩
void compress_up();
//向左移动
void move_up();

// 合并
void merge_down();
// 压缩
void compress_down();
//向左移动
void move_down();

// 在随机的位置生成一个随机的数字
void get_randnumber();
//判断游戏结束 获得胜利 还是继续游戏
int Is_game_close();
//获得添加数字
void get_number();
void add_number();
//获得一个 2or4的数字
int Get_2_4();
//把原来数组和当前数组进行判断
int Is_effect_change();
//拷贝原来数组
void copy_origin_array();

#endif
