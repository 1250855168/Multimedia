#include "Eraser.h"
#include "Lcd.h"

int main()
{
    Eraser e;
    printf("Present Line: %d\n", __LINE__);     // 所在行
    printf("Present Function: %s\n", __func__); // 函数名
    e.gaming();

    return 0;
}
