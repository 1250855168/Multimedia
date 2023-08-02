# 多媒体娱乐盒项目

- **每个项目我都会介绍 他们底层的C语言代码实现**  
- **我选择了 2048小游戏和多媒体播放器 进行了linux-arm开发板上如何使用图片的讲解**
- **在linux-arm开发板的依赖我也会进行说明**

## 2048小游戏

<img src="image\image-20230802192836220.png" alt="这是一个在线的2048小游戏的图片" style="zoom: 50%;" />

​																										**这是一个在线的2048小游戏的图片**			



-  我们用C语言实现这个游戏  主要是通过一个4*4的二维数组进行显示

- 和游戏本身一样我是通过按压上下左右进行数字的合并

- 通过上下左右的数组合并 和 打印这个二维数组 就能完成这个游戏的效果

  

下面我们通过代码进行详细讲解

```c
static int array[ROW][COL] = {//进行游戏显示的数组
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};
static int temp[ROW][COL] = {//进行临时合并的数组
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0},
    {0, 0, 0, 0}};

static int sum=0;//计算游戏的总得分
```

```C
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

//我们需要和原始游戏设置一样默认在二维数组上面生成两个数组 2 或者 4 
//可以通过Get_2_4();这个函数调整2和4生成的概率
void show_ui(int (*array)[4], int row, int col,int sum)
{
    // 清理屏幕
    system("clear");
    // 再显示新的数据
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            printf("%d  ", array[i][j]);
        }
        printf("\n");
    }
    printf("你获得的分数为：%d\n",sum);
}
```

```c
//这是一个游戏主要框架 
//我们给他进行一一进行解释

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
```

```c
//我们通过 w s a d进行数字的移动方向 在这里进行阻塞
Direction get_direction()
{
    Direction d;
    char c;
    scanf("%c", &c);
    getchar(); // 从输入缓冲区读取多余的\n, 丢弃不要
    printf("c = %d \n", c);
    switch (c)
    {
    case 'w':
        d = UP;
        break;
    case 's':
        d = DOWN;
        break;
    case 'a':
        d = LEFT;
        break;
    case 'd':
        d = RIGHT;
        break;
    default:
        d = UNKNOW;
        break;
    }
    return d;
}
```

```c
//得到方向
//我们用一个left代码讲解 其余三个方向类似

//我们需要将以前的二维数组拷贝到那个临时数组中
//我们需要进行临时和真的数组进行比较

/*
2 2 2 2 =>  4 4 0 0
2 0 2 0 =>  4 0 0 0
2 0 0 2 =>  4 0 0 0
0 0 0 2 =>  2 0 0 0  //这是需要完成的情况

int b[4] = {2, 2, 2, 2}; => {4, 0, 4, 0}//这是进行一次压缩形成的情况
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


```

```C
//压缩就是把一行或者一列里面 如{2,0,2,0} ->{2,2,0,0}
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
//然后我们进行合并{2,2,0,0}->{4,0,0,0}
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
//为什么我们还需要在进行一次合并呢！！
//可能我们的情况是这样的{2,2,2,2} 我们第一次压缩 {2,2,2,2}
//我们进行一次合并{4,0,4,0} 所以我们还需要进行一次{4,4,0,0}才算完成

//我们进行有效数组移动的判断  如果是 我们需要在添加一个数字
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
```

```c
//移动完成后 我们添加新数组  然后我们需要判断游戏是否继续

//出现2048 游戏直接胜利结束

//如果二维数组没有0
//且数字旁边没有相同的数字 
//游戏结束
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
```

- 上面的C原因在终端可以调试显示的结果

  gcc game.c input.c output.c main.c -o main

  ./main

  <img src="image\image-20230802201345523.png" alt="image-20230802201345523" style="zoom:80%;" />

- 下面我们就行Linux-arm开发板的处理

  - 我们需要就行arm-linux- arm编译的的处理 这里我们可以在window上面下载他的压缩文件拿到linux进行解压

  - 然后我们把他的解压文件下的bin文件夹配置到环境变量下面 我是配置在 ~.bashrc文件下面

  - ```shell
    sudo apt-get install gcc-arm-linux-gnueabihf
    
    //打开 .bashrc 文件
    export ARCH=arm
    export CROSS_COMPILE=arm-linux-gnueabihf-
    export PATH=$PATH:你自己的这个路径arm-linux-gnueabihf/bin
    
    find / -name arm-linux-gnueabihf/bin
    
    ```

- 我需要进行jpg图片显示

  ```
  //下载 JPG 库
  wget https://www.ijg.org/files/jpegsrc.v9d.tar.gz
  tar -zxvf jpegsrc.v9d.tar.gz
  
  cd jpeg-9d
  ./configure --host=arm-linux --prefix=/usr/local/jpeg
  make
  sudo make install
  
  --host 指定编译器  --prefix指定安装路径
  
  编辑 .bashrc 文件
  export LD_LIBRARY_PATH=你自己的jpg动态库的安装路径:$LD_LIBRARY_PATH
  source ~/.bashrc
  
  arm-linux-gnueabihf-pkg-config --cflags --libs libjpeg 进行测试是否安装成功
  
  ```

  ```c
  //进行图片对显示
  
  //我们可以把他封装成自己的 .c 于 .h的文件给自己调用
  
      /*
      首先，使用 ioctl 函数获取 fbdev 设备的信息，包括可变信息 vinfo 和固定信息 finfo。可变信息包括屏幕的分辨率、颜色深度等信息，固定信息包括显存的大小和起始地址等信息。
  
  然后，使用 mmap 函数将帧缓存设备的内存映射到用户空间的内存中，返回的指针 framebuffer 指向映射后的内存。在这里，我们使用 MAP_SHARED 标志来共享该内存区域，从而允许其他进程访问帧缓存。
  
  接下来，使用两个循环来遍历解码后的 JPG 图像数据。在内层循环中，将每个像素点的 RGB 值转换为 32 位的颜色值（ARGB 格式），并将该颜色值写入帧缓存的内存中。在这里，我们使用 finfo.line_length 变量来计算每行像素点在内存中占用的字节数，从而确定每个像素点的内存地址。
  
  最后，使用 munmap 函数来取消内存映射，释放内存资源。
  
  需要注意的是，在写入帧缓存设备的内存时，需要确保帧缓存设备和 JPG 图像的分辨率一致，否则图像会被拉伸或缩小，影响显示效果。
  */
  
  #include <stdio.h>
  #include <stdlib.h>
  #include <unistd.h>
  #include <fcntl.h>
  #include <sys/mman.h>
  #include <sys/ioctl.h>
  #include <linux/fb.h>
  #include <jpeglib.h>
  
  /**
   * 在 LCD 屏幕的指定位置显示指定路径的 JPG 图像
   *
   * @param fbdev_path  帧缓存设备的路径
   * @param jpg_path    JPG 图像的路径
   * @param x           图像在 LCD 屏幕中的水平起始位置
   * @param y           图像在 LCD 屏幕中的垂直起始位置
   * @return            成功返回 0，失败返回其他值
   */
  int display_jpg(const char* fbdev_path, const char* jpg_path, int x, int y) {
      // 打开帧缓存设备
      int fb = open(fbdev_path, O_RDWR);
      if (fb < 0) {
          fprintf(stderr, "Failed to open framebuffer device\n");
          return 1;
      }
  
      // 获取 fbdev 设备信息
      struct fb_var_screeninfo vinfo;
      struct fb_fix_screeninfo finfo;
      /*
      在执行这两个命令之后，vinfo 和 finfo 分别存储了帧缓存设备的可变参数和固定参数。具体来说，vinfo 中包含了像素格式、分辨率、虚拟分辨率等与图像显示相	关的参数，finfo 中包含了显存的起始地址、显存长度等与显存相关的参数。
      */
      ioctl(fb, FBIOGET_VSCREENINFO, &vinfo);
      ioctl(fb, FBIOGET_FSCREENINFO, &finfo);
  
      // 映射 fbdev 设备内存
      char* framebuffer = (char*)mmap(0, finfo.smem_len, PROT_READ | PROT_WRITE, MAP_SHARED, fb, 0);
      if (framebuffer == MAP_FAILED) {
          fprintf(stderr, "Failed to mmap framebuffer\n");
          return 1;
      }
  
      // 打开 JPG 文件并进行解码
      FILE* jpg_file = fopen(jpg_path, "rb");
      if (jpg_file == NULL) {
          fprintf(stderr, "Failed to open JPG file\n");
          return 1;
      }
  
      struct jpeg_decompress_struct cinfo;
      struct jpeg_error_mgr jerr;
  
      cinfo.err = jpeg_std_error(&jerr);
      jpeg_create_decompress(&cinfo);
      jpeg_stdio_src(&cinfo, jpg_file);
      jpeg_read_header(&cinfo, TRUE);
      jpeg_start_decompress(&cinfo);
  
      // 将解码后的图像数据写入 fbdev 设备内存
      for (int i = 0; i < cinfo.output_height; i++) {
          JSAMPROW row = (JSAMPROW)malloc(cinfo.output_width * cinfo.output_components);
          jpeg_read_scanlines(&cinfo, &row, 1);
  
          for (int j = 0; j < cinfo.output_width; j++) {
              unsigned int color = ((unsigned int)row[j*cinfo.output_components] << 16) | ((unsigned int)row[j*cinfo.output_components+1] << 8) | (unsigned int)row[j*cinfo.output_components+2];
              *((unsigned int*)(framebuffer + (y + i) * finfo.line_length + (x + j) * 4)) = color;
          }
  
          free(row);
      }
  
      // 清理资源并关闭文件和设备
      jpeg_finish_decompress(&cinfo);
      jpeg_destroy_decompress(&cinfo);
      fclose(jpg_file);
      munmap(framebuffer, finish.smem_len);
      close(fb);
  
      return 0;
  }
  
  //重这个代码可以看出 每次都要进行 /dev下的open close 特别影响效率
  
  //我们可以把 LCD 定义一个全局变量 进行一次的open 映射 解映射  close
  
  ```

  ```c
  /*触摸屏和显示屏可以有不同的分辨率，这是很常见的情况。分辨率不同可能会影响触摸屏的精度和准确性，因为触摸屏的坐标位置是基于其自身的坐标系计算的，而不是基于显示屏的坐标系计算的。因此，如果分辨率不同，可能需要进行一些校准来确保触摸屏的坐标与显示屏的坐标一致。*/
  
  //我们通过线程 运行这个函数就可以 拿到触摸方向和按压状态 -lpthread
  
  #include <stdio.h>
  #include <stdlib.h>
  #include <fcntl.h>
  #include <unistd.h>
  #include <linux/input.h>
  
  #define DEVICE_PATH "/dev/input/event0"
  #define SCREEN_WIDTH  800
  #define SCREEN_HEIGHT 480
  #define TOUCH_SCREEN_X  1024
  #define TOUCH_SCREEN_Y 600
  #define SWIPE_THRESHOLD_X 100  // 横向滑动的阈值
  #define SWIPE_THRESHOLD_Y 100  // 纵向滑动的阈值
  
  int main()
  {
      int fd = open(DEVICE_PATH, O_RDONLY);
      if (fd < 0) {
          perror("open");
          exit(1);
      }
  
      int x_start = 0, y_start = 0;  // 记录触摸点滑动的起始位置
      int x_end = 0, y_end = 0;      // 记录触摸点滑动的结束位置
      int pressed = 0;               // 记录触摸点的按压状态
      while (1) {
          struct input_event ev;
          int n = read(fd, &ev, sizeof(struct input_event));
          if (n < 0) {
              perror("read");
              exit(1);
          }
  
          if (ev.type == EV_ABS && (ev.code == ABS_X || ev.code == ABS_Y)) {
              int value = ev.value;
              if (ev.code == ABS_X) {
                  if (!pressed) {
                      x_start = value;         
                      x_start = x_start/TOUCH_SCREEN_X;
                  } else {
                      x_end = value;
                     x_end = x_end/TOUCH_SCREEN_X;
                  }
              } else {
                  if (!pressed) {
                      y_start = value;
                     y_start = y_start/TOUCH_SCREEN_Y;
                  } else {
                      y_end = value;
                      y_end = y_end/TOUCH_SCREEN_Y;
                  }
              }
          } else if (ev.type == EV_KEY && ev.code == BTN_TOUCH) {
              pressed = ev.value;
              if (!pressed) {
                  int x_diff = x_end - x_start;
                  int y_diff = y_end - y_start;
                  if (abs(x_diff) > abs(y_diff) && abs(x_diff) > SWIPE_THRESHOLD_X) {
                      if (x_diff > 0) {
                          printf("right\n");
                      } else {
                          printf("left\n");
                      }
                  } else if (abs(y_diff) > abs(x_diff) && abs(y_diff) > SWIPE_THRESHOLD_Y) {
                      if (y_diff > 0) {
                          printf("down\n");
                      } else {
                          printf("up\n");
                      }
                  } else {
                      printf("click: (%d, %d)\n", x_end, y_end);
                  }
              }
          }
      }
  
      close(fd);
      return 0;
  }
  ```

  ```makefile
  #指定可执行文件的名字
  TARGET := main
  
  #指定编译器
  CC := arm-linux-gcc
  
  #CSRC指定工程中所有的C源文件列表
  CSRCS := $(wildcard *.c)
  
  #OBJS指定工程中所有的.o文件列表
  OBJS := $(patsubst %.c,%.o,$(CSRCS))
  
  #INCS指定头文件的目录
  INCS += -I ./ -I ../inc -I /home/china/arm-jpeg/include
  
  #LIBS指定所需要依赖的库以及库的搜索路径
  LIBS += -L ../lib -L /home/china/arm-jpeg/lib -l jpeg -l pthread
  
  #可执行文件的编译规则
  $(TARGET) : $(OBJS)
  	$(CC) $^ $(LIBS) -o $@
  
  #.o文件的编译规则
  %.o : %.c
  	$(CC) -c $< $(INCS) -o $@
  	
  #"清除":所有的中间文件和最终的可执行文件
  clean:
  	rm -rf $(OBJS)
  	rm -rf $(TARGET)
  install:
  	cp main /mnt/hgfs/Yang    #下载到共享目录下面
  ```

  

## 消消乐小游戏



## 贪吃蛇小游戏



## 多媒体播放器
