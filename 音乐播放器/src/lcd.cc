#include "lcd.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include "jpeglib.h"
#include <sys/mman.h>
#include <stdlib.h>
#include <new>

// 代码一运行就初始化创建实例 ，本身就线程安全
lcd *lcd::g_pSingleton = new (std::nothrow) lcd();

lcd *lcd::GetInstance()
{
    return g_pSingleton;
}

void lcd::deleteInstance()
{
    if (g_pSingleton)
    {
        delete g_pSingleton;
        g_pSingleton = nullptr;
    }
}

int lcd::Lcd_Init(void)
{
    // 打开屏幕文件
    Fd_Lcd = open(LCD_PATH, O_RDWR);
    if (Fd_Lcd == -1)
    {
        perror("打开屏幕文件失败");
        return -1;
    }

    // 将屏幕文件映射到内存中去
    Plcd = (int *)mmap(NULL, 480 * 800 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, Fd_Lcd, 0);
    if (Plcd == MAP_FAILED)
    {
        perror("映射屏幕文件失败");
        return -1;
    }
    return 0;
}

void lcd::Lcd_Uinit(void)
{
    munmap(Plcd, 800 * 480 * 4);
    close(Fd_Lcd);
}

/*
    Lcd_DrawPoint:将指定的(x,y)处的像素点显示成color颜色
*/
void lcd::Lcd_DrawPoint(int x, int y, int color)
{
    if (x >= 0 && x < 800 && y >= 0 && y < 480)
    {
        *(Plcd + 800 * y + x) = color;
    }
}

/*
    Lcd_DisplayBMP:将bmppath指定的BMP文件显示到指定的位置上
        @x0,y0      BMP文件的显示起点(左上顶点)
        @bmppath    要显示的BMP文件的路径
        @return     显示成功返回0,显示失败返回-1
*/
int lcd::Lcd_DisplayBMP(int x0, int y0, char *bmppath)
{
    // 打开BMP文件
    int fdbmp = open(bmppath, O_RDONLY);
    if (fdbmp == -1)
    {
        perror("打开BMP文件失败");
        return -1;
    }

    unsigned char buf[4] = {0};
    // 判断bmppath是不是BMP文件
    int ret = read(fdbmp, buf, 2);
    if (ret == -1)
    {
        perror("读取BMP文件魔数失败");
        close(fdbmp);
        return -1;
    }
    if (buf[0] == 0x42 && buf[1] == 0x4D)
    {
        // 将光标偏移至宽度数据之前
        lseek(fdbmp, 0x12, SEEK_SET);

        // 读取宽度数据
        ret = read(fdbmp, buf, 4);
        if (ret == -1)
        {
            perror("读取BMP文件宽度失败");
            close(fdbmp);
            return -1;
        }

        // 还原宽度数据
        int width = (buf[3] << 24) | (buf[2] << 16) | (buf[1] << 8) | buf[0];

        // 将光标偏移至高度数据之前
        lseek(fdbmp, 0x16, SEEK_SET);

        // 读取高度数据
        ret = read(fdbmp, buf, 4);
        if (ret == -1)
        {
            perror("读取BMP文件高度失败");
            close(fdbmp);
            return -1;
        }

        // 还原高度数据
        int height = (buf[3] << 24) | (buf[2] << 16) |
                     (buf[1] << 8) | buf[0];

        // 将光标偏移至色深数据之前
        lseek(fdbmp, 0x1C, SEEK_SET);

        // 读取色深数据
        ret = read(fdbmp, buf, 2);
        if (ret == -1)
        {
            perror("读取BMP文件色深失败");
            close(fdbmp);
            return -1;
        }

        // 还原色深数据
        int depth = (buf[1] << 8) | buf[0];

        printf("%s is a bmp file,width[%d] height[%d] depth[%d]\n", bmppath, width, height, depth);

        // 求出BMP文件中像素数组一行所占字节数
        int bytesbmpline = abs(width) * (depth / 8);

        // 求出赖子的个数
        int laizi = 0;
        if (bytesbmpline % 4)
        {
            laizi = 4 - bytesbmpline % 4;
        }

        // 求出内存中用来保存像素数组的空间一行所占字节数
        int bytesmemline = bytesbmpline + laizi;

        // 求出内存中用来保存像素数组的空间的大小
        int size = bytesmemline * abs(height);

        // 开辟用来保存像素数组的内存空间
        char *p = (char *)malloc(size);

        // 先将光标偏移到像素数组之前
        lseek(fdbmp, 54, SEEK_SET);

        // 将像素数组读取到p指向的空间中去
        ret = read(fdbmp, p, size);
        if (ret == -1)
        {
            perror("读取像素数组失败");
            close(fdbmp);
            return -1;
        }

        unsigned char a, r, g, b;
        unsigned int color;
        int i = 0;
        // 对数据进行整合处理写入到映射区域即可
        int x, y; // x,y代表的是BMP文件中像素点的坐标
        for (y = 0; y < abs(height); y++)
        {
            for (x = 0; x < abs(width); x++)
            {
                // 每次从p指向的空间中取三个字节(前提条件是色深是24位的)
                // 如果是32位的色深,那么就需要每次取四个字节
                b = p[i++];
                g = p[i++];
                r = p[i++];
                if (depth == 32)
                {
                    a = p[i++];
                }
                else if (depth == 24)
                {
                    a = 0x00;
                }

                color = (a << 24) | (r << 16) | (g << 8) | b;

                // 将BMP文件中(x,y)处的像素点显示到映射区域对应的位置上
                Lcd_DrawPoint(x + x0, y0 + height - 1 - y, color);
            }
            i += laizi;
        }

        close(fdbmp);
        free(p);
    }
    else
    {
        printf("%s is not a bmp file!\n", bmppath);
        close(fdbmp);
        return -1;
    }

    return 0;
}

/*
    Lcd_DisplayJPG:在指定位置(x0,y0)出显示一张JPEG图片
*/
int lcd::Lcd_DisplayJPG(int x0, int y0, char *jpgfile)
{
    /* Step 1: 分配并初始化一个jpeg解压缩对象 */
    // struct jpeg_decompress_struct定义在libjpeg库中
    // 是用来保存一个解压jpeg文件所需要的信息(比如宽度/高度等信息)用的
    struct jpeg_decompress_struct cinfo;

    // struct jpeg_error_mgr定义在libjpeg库中
    // 是用来保存解压缩过程中的一些出错信息用的
    struct jpeg_error_mgr jerr;

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo); // 初始化cinfo这个解压对象

    /* Step 2: 指定要解压的JPEG文件 */
    FILE *infile = fopen(jpgfile, "r");
    if (infile == NULL)
    {
        perror("打开JPG图片失败");
        return -1;
    }

    jpeg_stdio_src(&cinfo, infile); // 指定要解压的JPEG文件

    /* Step 3: 调用jpeg_read_header获取图像信息(比如：宽/高等) */
    jpeg_read_header(&cinfo, TRUE);

    /* Step 4: 设置一些jpeg解压对象cinfo的一些参数，一般采用默认参数 */

    /* Step 5: 开始解压缩 */
    jpeg_start_decompress(&cinfo);

    /* Step 6: 读取一行或者多行扫描线上的数据并处理(将其显示到屏幕的对应位置上去) */
    unsigned char *buffer = (unsigned char *)malloc(cinfo.output_width * cinfo.output_components);

    int x;
    unsigned char a, r, g, b;
    unsigned int color;
    // cinfo.output_scanline表示现在已经解压扫描读取了多少行的数据,初始值为0
    while (cinfo.output_scanline < cinfo.output_height)
    {
        // 第一个参数表示解压对象
        // 第二个参数表示保存解压后的数据的空间(二级指针)
        // 第三个参数表示读取多少行数据进行解压
        jpeg_read_scanlines(&cinfo, &buffer, 1);

        unsigned int i = 0;
        // cinfo.output_scanline 自动+1
        // 将读取出来并解压缩的JPEG的一行显示到屏幕的对应位置上去
        for (x = 0; x < cinfo.output_width; x++) // 遍历这一行所有的像素点
        {
            // 取当前像素点的四个分量
            if (cinfo.output_components == 4)
            {
                a = buffer[i++];
            }
            else
            {
                a = 0x00;
            }
            r = buffer[i++];
            g = buffer[i++];
            b = buffer[i++];
            color = (a << 24) | (r << 16) | (g << 8) | b;

            Lcd_DrawPoint(x0 + x, y0 + cinfo.output_scanline - 1, color);
        }
    }

    /* Step 7: 调用jpeg_finish_decompress完成解压 */
    jpeg_finish_decompress(&cinfo);

    /* Step 8: 调用jpeg_destroy_decompress销毁解压缩对象 */
    jpeg_destroy_decompress(&cinfo);

    free(buffer);
    fclose(infile);

    return 0;
}