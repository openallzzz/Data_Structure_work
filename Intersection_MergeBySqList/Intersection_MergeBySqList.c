#include <stdio.h>
#include <stdlib.h>

typedef int DataType; /* 一改多改 */

 /* 设计动态顺序表*/
typedef struct
{
    DataType* a;  //动态开辟的数组
    int size;     //有效数据个数
    int capacity; //容量
}SqList;

void SqListInit(SqList* s);//初始化顺序表
void SqListPrint(SqList* s);//打印顺序表
void SqListCheckcapacity(SqList *p);//给顺序表扩容
void SqListPushBack(SqList* p, DataType X);//尾插
int SqListFindElem(SqList *p, DataType target);//查找顺序表中的指定元素

//求交集
SqList Intersection(SqList* p1, SqList* p2);
//求并集
SqList Merge(SqList* p1, SqList* p2);

int main()
{
    //利用顺序表构造第一个集合
    SqList tmp1;
    SqListInit(&tmp1);
    SqListPushBack(&tmp1, 7);
    SqListPushBack(&tmp1, 1);
    SqListPushBack(&tmp1, 2);
    SqListPushBack(&tmp1, 5);
    //利用顺序表构造第二个集合
    SqList tmp2;
    SqListInit(&tmp2);
    SqListPushBack(&tmp2, 5);
    SqListPushBack(&tmp2, 6);
    SqListPushBack(&tmp2, 2);
    SqListPushBack(&tmp2, 10);
    SqListPushBack(&tmp2, 4);


    //打印第一个集合
    SqListPrint(&tmp1);
    //打印第二个集合
    SqListPrint(&tmp2);

    // 0: 求交集
    SqList newlist01 = Intersection(&tmp1, &tmp2);
    printf("交集为：");
    SqListPrint(&newlist01);

    // 1: 求并集
    SqList newlist02 = Merge(&tmp1, &tmp2);
    printf("\n并集为：");
    SqListPrint(&newlist02);
    return 0;
}

void SqListCheckcapacity(SqList *p)
{
    if(p->size >= p->capacity)
    {
        p->capacity *= 2;
        p->a = (DataType*)realloc(p->a, sizeof(DataType) * p->capacity);
        if(p->a == NULL)
        {
            printf("增容失败");
            exit(0);
        }
    }
}

void SqListInit(SqList* s)
{

    s->a = (DataType*)malloc(sizeof(DataType) * 4);
    if(s->a == NULL)
    {
        printf("申请内存失败");
        exit(0);
    }
    s->size = 0;
    s->capacity = 4;

}

void SqListPrint(SqList* s)
{
    int i = 0;
    for(i = 0; i < s->size; i++)
        printf("%d ",s->a[i]);
    printf("\n");
}
void SqListPushBack(SqList* p, DataType X)
{
    //增容---容量大小必须比当前已存在的结点个数多
    //即 capacity > size
    SqListCheckcapacity(p);
    p->a[p->size] = X;
    p->size++;
}
int SqListFindElem(SqList *p, DataType target)
{
    for(int i = 0; i < p->size; i++)
    {
        if(target == p->a[i])
            return i;
    }
    return -1;
}
SqList Intersection(SqList* p1, SqList* p2)
{
    SqList res;
    SqListInit(&res);
    for(int i = 0; i < p1->size; i++)
    {
        if((SqListFindElem(p2, p1->a[i])) != -1)
        {
            SqListPushBack(&res, p1->a[i]);
        }
    }
    return res;
}
SqList Merge(SqList* p1, SqList* p2)
{
    SqList res;
    SqListInit(&res);
    for(int i = 0; i < p1->size; i++)
    {
        if(SqListFindElem(p2, p1->a[i]) < 0)
        {
            SqListPushBack(p2, p1->a[i]);
        }
    }

    for(int i = 0; i < p2->size; i++)
        SqListPushBack(&res, p2->a[i]);
    return res;
}


