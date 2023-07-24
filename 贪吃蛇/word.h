#ifndef __WROD_H__
#define __WROD_H__

#include "lcd.h"

#define SCHOOLNAMEW 40
#define SCHOOLNAMEH 35

/*
   Lcd_DrawWord:在位置为(x0,y0)处显示宽为w,高为h,颜色为color的汉字	
*/
void Lcd_DrawWord(int x0,int y0,int w,int h,char *data,int color);

/*
    Lcd_DisplaySchoolName:在屏幕上显示学校名
*/
void Lcd_DisplaySchoolName(void);

#endif

