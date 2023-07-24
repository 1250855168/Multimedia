
#define LCD_PATH "/dev/fb0"
class lcd
{
private:
    int Fd_Lcd;

    int *Plcd;

    // 将其构造和析构成为私有的, 禁止外部构造和析构
    lcd() = default;
    ~lcd() = default;

    // 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
    lcd(const lcd &l);
    const lcd &operator=(const lcd &l);

    // 唯一单实例对象指针
    static lcd *g_pSingleton;

public:
    // 获取单实例
    static lcd *GetInstance();

    // 释放单实例，进程退出时调用
    static void deleteInstance();

    int Lcd_Init(void);

    void Lcd_Uinit(void);

    int Lcd_DisplayBMP(int x0, int y0, char *bmppath);

    int Lcd_DisplayJPG(int x0, int y0, char *jpgfile);

    void Lcd_DrawPoint(int x, int y, int color);
};
