#include <stdio.h>
#include <stdlib.h>
typedef int SLDataType;

typedef struct SListNode
{
    SLDataType coef; //coefficient
    SLDataType expon; //exponent
    struct SListNode* next;
}SListNode;

void SListPrint(SListNode* p);
SListNode* BuySListNode(SLDataType coef, SLDataType expon);
void SListPushBack(SListNode** pphead, SLDataType coef, SLDataType expon);
SListNode* BubbleSortSList(SListNode* head);
SListNode* polyAdd(SListNode* p1, SListNode* p2);

int main()
{
    //创建第一个多项式
    SListNode* plist1 = NULL;
    SListPushBack(&plist1, 4, 2);
    SListPushBack(&plist1, 3, 1);
    SListPushBack(&plist1, 5, 4);
    SListPushBack(&plist1, 7, 6);
    SListPrint(BubbleSortSList(plist1));
    //创建第二个多项式
    SListNode* plist2 = NULL;
    SListPushBack(&plist2, 6, 3);
    SListPushBack(&plist2, 11, 1);
    SListPushBack(&plist2, -5, 4);
    SListPushBack(&plist2, 9, 6);
    SListPrint(BubbleSortSList(plist2));

    printf("\n两个多项式相加为：");
    SListNode* p = polyAdd(plist1, plist2);

    SListPrint(p);

    return 0;
}

void SListPrint(SListNode* p)
{
    if(p)
    {
        printf("%dx^%d",p->coef, p->expon);
        p = p->next;
    }
    while(p)
    {
        printf(" + %dx^%d",p->coef, p->expon);
        p = p->next;
    }
    printf("\n");
}
SListNode* BuySListNode(SLDataType coef, SLDataType expon)
{
    SListNode* newNode = (SListNode*)malloc(sizeof(SListNode));
    if(newNode == NULL)
    {
        printf("申请内存失败");
        exit(0);
    }
    newNode->coef  = coef;
    newNode->expon = expon;
    newNode->next  = NULL;
    return newNode;
}
void SListPushBack(SListNode** pphead, SLDataType coef, SLDataType expon)
{
    SListNode* newNode = BuySListNode(coef, expon);
    if(*pphead == NULL)
        *pphead = newNode;
    else
    {
        SListNode* tail = *pphead;
        //找尾结点
        while(tail->next != NULL)
        {
            tail = tail->next;
        }
        tail->next = newNode;
    }
}
SListNode* BubbleSortSList(SListNode* head)//对链表进行冒泡排序
{
    if(head == NULL || head->next == NULL)
        return head;
    SListNode* p = NULL;
    int isChange = 1;
    while(p != head->next && isChange)
    {
        SListNode* q = head;
        isChange = 0;
        for(;q->next && q->next != p; q = q->next)
        {
            if(q->expon > q->next->expon)
            {
                SLDataType tmp = q->coef;
                q->coef = q->next->coef;
                q->next->coef = tmp;
                SLDataType tmp1 = q->expon;
                q->expon = q->next->expon;
                q->next->expon = tmp1;

                isChange = 1;
            }
        }
        p = q;
    }
    return head;
}
SListNode* polyAdd(SListNode* p1, SListNode* p2)
{
    SListNode* newHead = NULL;

    while(p1 && p2)
    {
        if(p1->expon < p2->expon)
        {
            SListPushBack(&newHead, p1->coef, p1->expon);
            p1 = p1->next;
        }
        else if(p1->expon == p2->expon)
        {
            if( (p1->coef + p2->coef) != 0)
            {
                SListPushBack(&newHead, p1->coef+p2->coef, p1->expon);
            }
            //如果这个迭代关系下载判断里面的话，可能会遇到死循环
            //最好的方法是将其写在外面
            p1 = p1->next;
            p2 = p2->next;
        }
        else
        {
            SListPushBack(&newHead, p2->coef, p2->expon);
            p2 = p2->next;
        }
    }
    if(p1 == NULL)
    {
        while(p2)
        {
            SListPushBack(&newHead, p2->coef, p2->expon);
            p2 = p2->next;
        }
    }
    else
    {
        while(p1)
        {
            SListPushBack(&newHead, p1->coef, p1->expon);
            p1 = p1->next;
        }
    }
    return newHead;
}
