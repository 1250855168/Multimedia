#pragma once

#include "head.h"
#include "jpeglib.h"
#include "head.h"

#define LCD_PATH "/dev/fb0"

class Lcd
{
private:
    int Fd_Lcd;

    int *Plcd;

public:
    Lcd();
    ~Lcd();

    int getlcd()
    {
        return Fd_Lcd;
    }

    /*
        Lcd_Init:屏幕的初始化函数
    */
    int Lcd_Init(void);

    /*
        Lcd_Uinit:屏幕的解初始化函数
    */
    void Lcd_Uinit(void);

    /*
        Lcd_DrawPoint:将指定的(x,y)处的像素点显示成color颜色
    */
    void Lcd_DrawPoint(int x, int y, int color);

    /*
        Lcd_DrawRect:画矩形函数
            @x0,y0      矩形的左上顶点(起始点)的坐标
            @w,h        矩形的宽和高
            @color      矩形的颜色
    */
    void Lcd_DrawRect(int x0, int y0, int w, int h, int color);

    /*
        Lcd_DisplayBMP:将bmppath指定的BMP文件显示到指定的位置上
            @x0,y0      BMP文件的显示起点(左上顶点)
            @bmppath    要显示的BMP文件的路径
            @return     显示成功返回0,显示失败返回-1
    */
    int Lcd_DisplayBMP(int x0, int y0, char *bmppath);

    /*
        Lcd_DisplayJPG:在指定位置(x0,y0)出显示一张JPEG图片
    */
    int Lcd_DisplayJPG(int x0, int y0, char *jpgfile);
};
