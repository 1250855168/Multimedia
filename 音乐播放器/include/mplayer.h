#define PRE 1
#define NEXT 2
#define STOP 3
#define ADDSOUND 4
#define DISSOUND 5

#define PATHNAMEMP4 "./MP4"

class mplayer
{
private:
    int status; // 获得音频的状态

    // 将其构造和析构成为私有的, 禁止外部构造和析构
    mplayer() = default;
    ~mplayer() = default;

    // 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
    mplayer(const mplayer &l);
    const mplayer &operator=(const mplayer &l);

    // 唯一单实例对象指针
    static mplayer *g_pSingleton;

public:
    // 获取单实例
    static mplayer *GetInstance();

    // 释放单实例，进程退出时调用
    static void deleteInstance();

    int video_play();

    int get_status();
};