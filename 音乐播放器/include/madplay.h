#define PRE 1
#define NEXT 2
#define STOP 3
#define RESTORE 4
#define QUIT 5

#define PATHNAMEMP3 "./MP3"

class madplay
{
private:
    int status; // 获得音频的状态

    // 将其构造和析构成为私有的, 禁止外部构造和析构
    madplay() = default;
    ~madplay() = default;

    // 将其拷贝构造和赋值构造成为私有函数, 禁止外部拷贝和赋值
    madplay(const madplay &l);
    const madplay &operator=(const madplay &l);

    // 唯一单实例对象指针
    static madplay *g_pSingleton;

public:
    // 获取单实例
    static madplay *GetInstance();

    // 释放单实例，进程退出时调用
    static void deleteInstance();

    int music_play();

    int get_status();
};
