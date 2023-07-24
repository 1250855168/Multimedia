#include "DCList.h"

// 初始化链表
std::shared_ptr<DCList::Node> DCList::list_init(char *newdata)
{
    std::shared_ptr<Node> head = std::make_shared<Node>();
    head->data = newdata;
    head->next = head;
    head->prev = head;
    return head;
}

// 创建新节点
std::shared_ptr<DCList::Node> DCList::newnode(char *newdata)
{
    std::shared_ptr<Node> node = std::make_shared<Node>();
    node->data = newdata;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// 加入新节点
void DCList::addnode(std::shared_ptr<Node> node, std::shared_ptr<Node> list)
{
    std::shared_ptr<Node> p = list;
    while (p->next != list)
    {
        p = p->next;
    }
    node->prev = list->prev;
    node->next = list;
    list->prev = node;
    node->prev->next = node;
}
