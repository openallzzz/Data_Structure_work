#include <stdio.h>
#include <stdlib.h>

typedef int SListDataType;
//结点
typedef struct SListNode
{
    SListDataType data;
    struct SListNode* next;
}SListNode;

void SListPrint(SListNode* phead);//打印单链表
void SListPushBack(SListNode** pphead, SListDataType x);//尾插

SListNode* BuySListNode(SListDataType x);//创建结点

SListNode* mergeTwoList(SListNode* l1, SListNode* l2);


int main()
{
    //创建第一个链表 (非递减
    SListNode* PList01 = NULL;
    for(int i = 0; i < 13; i += 2)
    {
        SListPushBack(&PList01, i+1);
    }
    SListPrint(PList01);

    //创建第二个链表 (非递减
    SListNode* PList02 = NULL;
    for(int i = 0; i < 16; i += 3)
    {
        SListPushBack(&PList02, i+1);
    }
    SListPrint(PList02);

    SListNode* p = mergeTwoList(PList01, PList02);
    printf("\n合并后：");
    SListPrint(p);

    return 0;
}


void SListPrint(SListNode* phead)//打印单链表
{
    //遍历链表
    SListNode* cur = phead;

    while(cur != NULL)
    {
        printf("%d->",cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}
void SListPushBack(SListNode** pphead, SListDataType x)//单链表尾插
{
    SListNode* newNode = BuySListNode(x);

    if(*pphead == NULL)
    {
        *pphead = newNode;
    }
    else
    {
        SListNode* tail = *pphead;
        //找尾指针
        while(tail->next != NULL)
        {
            tail = tail->next;
        }
        //此时的tail即为尾指针

        //链接结点
        tail->next = newNode;
    }
}
SListNode* BuySListNode(SListDataType x)//创建单链表结点
{
    SListNode* newNode = (SListNode*)malloc(sizeof(SListNode));
    if(newNode == NULL)
    {
        printf("申请结点失败!\n");
        exit(0);
    }
    //完善结点
    newNode->data = x;
    newNode->next = NULL;

    return newNode;
}
//合并两个有序链表
SListNode* mergeTwoList(SListNode* l1, SListNode* l2)
{
    if(l1 == NULL)
        return l2;
    if(l2 == NULL)
        return l1;
// 1. 递归
    if(l1->data <= l2->data)
    {
        l1->next = mergeTwoList(l1->next, l2);
        return l1;
    }
    else
    {
        l2->next = mergeTwoList(l1, l2->next);
        return l2;
    }

// 2. 尾插
//    SListNode* newhead = NULL, *tail = NULL;
//    if(l1->data <= l2->data)
//    {
//        newhead = l1;
//        tail = newhead;
//        l1 = l1->next;
//    }
//    else
//    {
//        newhead = l2;
//        tail = newhead;
//        l2 = l2->next;
//    }
//    while(l1 && l2)
//    {
//        if(l1->data <= l2->data)
//        {
//            tail->next = l1;
//            l1 = l1->next;
//            tail = tail->next;
//        }
//        else
//        {
//            tail->next = l2;
//            l2 = l2->next;
//            tail = tail->next;
//        }
//    }
//    if(l1 == NULL)
//        tail->next = l2;
//    else
//        tail->next = l1;
//    return newhead;
}
