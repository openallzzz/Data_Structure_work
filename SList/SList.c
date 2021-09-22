#include <stdio.h>
#include <stdlib.h>

typedef int SListDataType;
//结点
typedef struct SListNode
{
    SListDataType data;
    struct SListNode* next;
} SListNode;

//测试集
void TestSList1();
//....
//....
//测试集

void SListPushBack(SListNode** pphead, SListDataType x);//尾插
void SListPopBack(SListNode** pphead);//尾删

void SListPushFront(SListNode** pphead, SListDataType x);//头插
void SListPopFront(SListNode** pphead);//头删

//打印单链表
void SListPrint(SListNode* phead);
//创建结点
SListNode* BuySListNode(SListDataType x);
//单链表的查找
SListNode* SListFind(SListNode* phead, SListDataType x);
//改变单链表中的指定元素
void ChangeSListElem(SListNode** pphead, SListDataType Elem, SListDataType target);

int main()
{
    TestSList1();
    return 0;
}
/*-----------打印单链表---------*/
void SListPrint(SListNode* phead)
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
/*-----------创建单链表结点-----------*/
SListNode* BuySListNode(SListDataType x)
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
/*-----------------单链表的尾插---------------------*/
void SListPushBack(SListNode** pphead, SListDataType x)
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

//单链表的尾删需要好好琢磨
/*------尾部删除单链表的结点--------*/
void SListPopBack(SListNode** pphead)
{
    if(*pphead == NULL)
    {
        return ;
    }
    else if((*pphead)->next == NULL)
    {
        free(*pphead);
        *pphead = NULL;
    }
    else
    {
        SListNode* prev = NULL;
        SListNode* tail = *pphead;
        while(tail->next != NULL)
        {
            prev = tail;
            tail = tail->next;
        }
        free(tail);
        prev->next = NULL;
    }
}

/*---------单链表的头部插入------------*/
void SListPushFront(SListNode** pphead, SListDataType x)
{
    SListNode* newNode = BuySListNode(x);

    //1. 空链表
    if(*pphead == NULL)
    {
        *pphead = newNode;
    }
    //2. 非空
    else
    {
        newNode->next = *pphead;
        *pphead = newNode;
    }

    //1和2 可以结合成一种情况 但是为了代码简单分明起见 还是分
    //两种情况来写
}
/*------单链表的头部删除------*/
void SListPopFront(SListNode** pphead)
{
    if(*pphead == NULL)
        return ;
    else
    {
        SListNode* next = (*pphead)->next;
        free(*pphead);//free之后不可再访问其内存
        *pphead = next;
    }
}
/*--------------------单链表的查找-------------------*/
SListNode* SListFind(SListNode* phead, SListDataType x)
{
    SListNode* cur = phead;
    while(cur)
    {
        if(cur->data == x)
            return cur;
        cur = cur->next;
    }
    return NULL;
}
void ChangeSListElem(SListNode** pphead, SListDataType Elem, SListDataType target)
{
    SListNode* pNode = SListFind(*pphead, Elem);
    if(pNode)
        pNode->data = target;
    else
        printf("未找到被指定修改的元素");
}
void TestSList1()
{
    SListNode* PList = NULL;
    SListPushBack(&PList, 5);
    SListPushBack(&PList, 5);
    SListPushBack(&PList, 5);
    SListPushBack(&PList, 5);
    SListPrint(PList);

    SListPopBack(&PList);
    SListPopBack(&PList);
    SListPopBack(&PList);
    SListPopBack(&PList);
    SListPrint(PList);

    SListPushFront(&PList, 7);
    SListPushFront(&PList, 6);
    SListPushFront(&PList, 5);
    SListPushFront(&PList, 4);
    SListPushFront(&PList, 3);
    SListPushFront(&PList, 2);
    SListPushFront(&PList, 1);
    SListPushFront(&PList, 0);
    SListPrint(PList);

    SListPopFront(&PList);
    SListPrint(PList);

    ChangeSListElem(&PList, 5, 520);
    SListPrint(PList);
}
