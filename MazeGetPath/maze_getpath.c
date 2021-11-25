#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 110

typedef struct Position
{
    int row; // 行
    int col; // 列
}PT; // 坐标

/*--------------------------------------*/
typedef struct stack
{
    PT* Path;
    int top;
    int capacity;
}stack;

void initStack(stack* s)
{
    s->Path = (PT*)malloc(sizeof(PT) * MAX_SIZE);
    s->capacity = MAX_SIZE;
    s->top = 0;
}

int IsEmpty(stack* s)
{
    return s->top == 0 ? 1 : 0;
}

void push(stack* s, PT cur)
{
    s->Path[s->top] = cur;
    s->top++;
}

void pop(stack* s)
{
    if (!IsEmpty(s))
    {
        s->top--;
    }
}

PT Top(stack* s)
{
    return s->Path[s->top - 1];
}

void Destory(stack* s)
{
    free(s->Path);
    s->Path = NULL;
    s->capacity = s->top = 0;
}

stack path;
/*-------------------------------------*/
void Print(int** a, int N, int M)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void PrintPath()
{
    stack rPath; // 借助rPath栈将路径上的点倒过去再输出栈
    initStack(&rPath);
    while (!IsEmpty(&path))
    {
        PT cur = Top(&path);
        push(&rPath, cur);
        pop(&path);
    }

    Destory(&path);

    while (!IsEmpty(&rPath))
    {
        PT cur = Top(&rPath);
        printf("(%d,%d)\n", cur.row, cur.col);
        pop(&rPath);
    }

    Destory(&rPath);
}

int IsPass(int** maze, int N, int M, PT cur) // 可以通过
{
    if (cur.row >= 0 && cur.row < N
        && cur.col >= 0 && cur.col < M
        && maze[cur.row][cur.col] == 0)
    {
        return 1; // 可以通过
    }
    else
    {
        return 0; // 不可以通过
    }
}

int GetMazePath(int** maze, int N, int M, PT cur)
{
    // 我们假设其一定是包含在路径中---进来的坐标先压入栈
    // 该点只有两种状态
    // 1. 包含在路径中  2. 不包含在路径中
    // 情况1我们已经压入栈了
    // 情况2在return false 之前将其出栈了
    // 可以确保栈里的元素就是路径中每个点的坐标
    push(&path, cur);
    if (cur.row == N - 1 && cur.col == M - 1)
    {
        return 1; // 找到了终点
    }
    PT next = cur;
    // 运行到这的坐标点一定是有效的
    maze[cur.row][cur.col] = 2; // 标志成已访问 （0 -- 空地；1 -- 墙；2 -- 已被访问）


    // 上
    next = cur;
    next.row -= 1; // cur上方的坐标
    if (IsPass(maze, N, M, next))
    {
        if (GetMazePath(maze, N, M, next))// 递归解决子问题
        {
            return 1;
        }
    }

    // 下
    next = cur;
    next.row += 1; // cur下方的坐标
    if (IsPass(maze, N, M, next))
    {
        if (GetMazePath(maze, N, M, next))// 递归解决子问题
        {
            return 1;
        }
    }

    // 左
    next = cur;
    next.col -= 1; // cur左方的坐标
    if (IsPass(maze, N, M, next))
    {
        if (GetMazePath(maze, N, M, next))// 递归解决子问题
        {
            return 1;
        }
    }

    // 右
    next = cur;
    next.col += 1; // cur右方的坐标
    if (IsPass(maze, N, M, next))
    {
        if (GetMazePath(maze, N, M, next))// 递归解决子问题
        {
            return 1;
        }
    }
    pop(&path);
    return 0; // 四个方向均不可通，返回上一个调用
}


int main()
{
    int N = 0, M = 0;
    while (scanf("%d %d", &N, &M) != EOF)
    {
        // 动态开辟二维数组
        int** maze = (int**)malloc(sizeof(int*) * N);
        for (int i = 0; i < N; i++)
        {
            maze[i] = (int*)malloc(sizeof(int) * M);
        }

        // 录入迷宫
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < M; j++)
            {
                scanf("%d", &maze[i][j]);
            }
        }
        // 自测上述代码
        //Print(maze, N, M);

        // 解决问题
        PT entry = { 0, 0 }; // 起点
        initStack(&path);
        int flag = GetMazePath(maze, N, M, entry);

        if (flag)
        {
            //printf("11");
            printf("该迷宫到出口的路径为：\n");
            PrintPath();
        }
        else
        {
            printf("该迷宫没有到出口的路径。");
        }

        // 释放动态开辟的空间
        for (int i = 0; i < N; i++)
        {
            free(maze[i]);
        }
        free(maze);
        maze = NULL;
    }

    return 0;
}