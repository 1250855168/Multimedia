
#include <iostream>
#include <memory>

class DCList
{
private:
public:
    // 设置节点
    struct Node
    {
        char *data;
        std::shared_ptr<Node> next;
        std::shared_ptr<Node> prev;
    };

    DCList(/* args */) = default;
    ~DCList() = default;

    // 初始化链表
    std::shared_ptr<Node> list_init(char *newdata);

    // 创建新节点
    std::shared_ptr<DCList::Node> newnode(char *newdata);

    // 加入新节点
    void addnode(std::shared_ptr<Node> node, std::shared_ptr<Node> list);
};
