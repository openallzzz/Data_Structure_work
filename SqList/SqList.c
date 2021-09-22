#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int DataType; /* 一改多改 */

 /* 设计动态顺序表*/
typedef struct
{
    DataType* a;  //动态开辟的数组
    int size;     //有效数据个数
    int capacity; //容量
}SqList;

//测试集
void TestSqList1();
//.....
//.....
//测试集

void SqListInit(SqList* s);//初始化顺序表
void SqListPrint(SqList* s);//打印顺序表
void SqListDestory(SqList* s);//销毁顺序表
void SqListCheckcapacity(SqList *p);//给顺序表扩容
// 头插尾插 头删尾删
void SqListPushBack(SqList* p, DataType X);
void SqListPopBack(SqList* p);
void SqListPushFront(SqList* p, DataType X);
void SqListPopFront(SqList* p);

//任意位置的插入与删除
void SqListInsert(SqList *p, int pos, DataType X);
void SqListErase(SqList *p, int pos);

//查找顺序表中的指定元素
int SqListFindElem(SqList *p, DataType target);

//更改顺序表中指定元素
void ChangeSqListElem(SqList *p, DataType elem, DataType target);

int main()
{
    TestSqList1();//测试顺序表的增删查改
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
    assert(s);
    int i = 0;
    for(i = 0; i < s->size; i++)
        printf("%d ",s->a[i]);
    printf("\n");
}

void SqListDestory(SqList* s)
{
    free(s->a);  //指向的那段空间被销毁
    s->a = NULL; //再把指针赋为空
    s->size = s->capacity  = 0;
}
void SqListPushBack(SqList* p, DataType X)
{
    assert(p);
    //增容---容量大小必须比当前已存在的结点个数多
    //即 capacity > size
    SqListCheckcapacity(p);
    p->a[p->size] = X;
    p->size++;
}

void SqListPopBack(SqList* p)
{
    assert(p);

    p->size--;
}

void SqListPushFront(SqList* p, DataType X)
{
    assert(p);
    SqListCheckcapacity(p);
    int i = 0;
    for(i = p->size; i>0; i--)
    {
        p->a[i] = p->a[i-1];
    }
    p->a[0] = X;
    p->size++;
}

void SqListPopFront(SqList* p)
{
    assert(p);
    int i = 0;
    for(i = 1; i<p->size; i++)
    {
        p->a[i-1] = p->a[i];
    }
    p->size--;
}

void SqListInsert(SqList *p, int pos, DataType X)
{
    assert(p);
    SqListCheckcapacity(p);
    int i = 0;
    for(i = p->size; i>pos; i--)
    {
        p->a[i] = p->a[i-1];
    }
    p->a[pos] = X;
    p->size++;
}

void SqListErase(SqList *p, int pos)
{
    int i = 0;
    for(i = pos; i<p->size-1; i++)
    {
        p->a[i] = p->a[i+1];
    }
    p->size--;
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
void ChangeSqListElem(SqList *p, DataType Elem, DataType target)
{
    int index = SqListFindElem(p, Elem);
    if(index != -1)
        p->a[index] = target;
    else
        printf("顺序表中无该元素");
}
void TestSqList1()
{
    SqList s;
    SqListInit(&s);
    SqListPushBack(&s,1);
    SqListPushBack(&s,2);
    SqListPushBack(&s,3);
    SqListPushBack(&s,4);
    SqListPushBack(&s,5);
    SqListPushBack(&s,6);
    SqListPrint(&s);

    SqListPopBack(&s);
    SqListPopBack(&s);
    SqListPrint(&s);

    SqListPushFront(&s,8);
    SqListPushFront(&s,9);
    SqListPushFront(&s,-1);
    SqListPrint(&s);

    SqListPopFront(&s);
    SqListPopFront(&s);
    SqListPrint(&s);

    SqListInsert(&s,4,9);
    SqListInsert(&s,5,9);
    SqListInsert(&s,6,9);
    SqListInsert(&s,7,9);
    SqListInsert(&s,8,9);
    SqListPrint(&s);

    SqListErase(&s,4);
    SqListErase(&s,2);
    SqListPrint(&s);

    int index = SqListFindElem(&s, 5);
    printf("%d\n",index);
    ChangeSqListElem(&s, 9, 7);
    SqListPrint(&s);
    SqListDestory(&s);
}

