#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
stack minpath;
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

void PrintPath(stack* ps)
{
    stack rPath;
    initStack(&rPath);
    while (!IsEmpty(ps))
    {
        PT cur = Top(ps);
        push(&rPath, cur);
        pop(ps);
    }

    while (!IsEmpty(&rPath))
    {
        PT cur = Top(&rPath);
        if (rPath.top == 1)
        {
            printf("[%d,%d]", cur.row, cur.col);
            pop(&rPath);
            continue;
        }

        printf("[%d,%d],", cur.row, cur.col);
        pop(&rPath);
    }

    Destory(&rPath);
}

int IsPass(int** maze, int N, int M, PT cur) // 可以通过
{
    if (cur.row >= 0 && cur.row < N
        && cur.col >= 0 && cur.col < M
        && maze[cur.row][cur.col] == 1)
    {
        return 1; // 可以通过
    }
    else
    {
        return 0; // 不可以通过
    }
}

void copy(stack* ppath, stack* min)
{
    min->Path = (PT*)malloc(sizeof(PT) * ppath->capacity);
    memcpy(min->Path, ppath->Path, sizeof(PT) * ppath->top);
    min->capacity = ppath->capacity;
    min->top = ppath->top;
}
void GetMazePath(int** maze, int N, int M, int P, PT cur)
{
    push(&path, cur);

    // 走到出口
    if (cur.row == 0 && cur.col == M - 1)
    {
        if ((path.top < minpath.top
            || IsEmpty(&minpath)) && P >= 0) // 更新最短路径
        {
            Destory(&minpath);
            copy(&path, &minpath);
        }
    }
    PT next = cur;
    // 运行到这的坐标点一定是有效的
    maze[cur.row][cur.col] = 2; // 标志成已访问 （0 -- 空地；1 -- 墙；2 -- 已被访问）


    // 上
    next = cur;
    next.row -= 1; // cur上方的坐标
    if (IsPass(maze, N, M, next))
    {
        GetMazePath(maze, N, M, P - 3, next);// 递归解决子问题
    }

    // 下
    next = cur;
    next.row += 1; // cur下方的坐标
    if (IsPass(maze, N, M, next))
    {
        GetMazePath(maze, N, M, P, next);// 递归解决子问题
    }

    // 左
    next = cur;
    next.col -= 1; // cur左方的坐标
    if (IsPass(maze, N, M, next))
    {
        GetMazePath(maze, N, M, P - 1, next);// 递归解决子问题
    }

    // 右
    next = cur;
    next.col += 1; // cur右方的坐标
    if (IsPass(maze, N, M, next))
    {
        GetMazePath(maze, N, M, P - 1, next);// 递归解决子问题
    }

    maze[cur.row][cur.col] = 1;
    pop(&path);
}

int main()
{
    int N = 0, M = 0, P = 0;
    while (scanf("%d %d %d", &N, &M, &P) != EOF)
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
        initStack(&minpath);
        GetMazePath(maze, N, M, P, entry);

        // 打印路径
        if (!IsEmpty(&minpath))
        {
            PrintPath(&minpath);
        }
        else
        {
            printf("Can not escape!");
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